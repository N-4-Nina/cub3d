/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:11:00 by abouchau          #+#    #+#             */
/*   Updated: 2020/09/27 11:01:19 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	int_size(int nb)
{
	int i;

	i = 1;
	while (nb / 10 != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	parse_res(char *line, t_param *p)
{
	int x;
	int y;

	p->window->x = abs(ft_atoi(line));
	p->window->y = abs(ft_atoi(line + int_size(p->window->x) + 1));
	mlx_get_screen_size(p->window->mlx, &x, &y);
	if (p->window->x > x)
		p->window->x = x;
	if (p->window->y > y)
		p->window->y = y;
	if (!(p->window->x) || !(p->window->y))
		return (0);
	return (1);
}

int	parse_color(char *line, t_color *color)
{
	int	r;
	int	g;
	int	b;
	int	convert;

	r = ft_atoi(&line[2]);
	g = ft_atoi(&line[2] + int_size(r) + 1);
	b = ft_atoi(&line[2] + int_size(r) + int_size(g) + 2);
	convert = r;
	convert = (convert << 8) + g;
	convert = (convert << 8) + b;
	if (line[0] == 'F')
		color->floor = convert;
	else if (line[0] == 'C')
		color->ceiling = convert;
	return (1);
}

int	parse_texture(int id, char *line, t_param *p)
{
	int	fd;
	int w;
	int h;

	w = 64;
	h = 64;
	while (*line == ' ')
		line++;
	fd = open(line, O_RDONLY);
	if (fd > 1)
	{
		close(fd);
		p->tex[id].img = mlx_xpm_file_to_image(p->window->mlx,
				line, &p->tex[id].w, &p->tex[id].h);
		p->tex[id].ptr = mlx_get_data_addr(p->tex[id].img,
				&p->tex[id].bpp, &p->tex[id].size_line, &p->tex[id].endian);
		//printf("parsed texture: %s; \n bpp: %d, sizeline: %d, endian: %d\n", line, p->tex[id].bpp, p->tex[id].size_line, p->tex[id].endian);
		return (1);
	}
	else
		return (0);
}

int	isvalid(char *line, t_param *p)
{
	int	ret;

	ret = 0;
	if (line[0] == 'R')
		ret = parse_res(&line[2], p);
	if (line[0] == 'N' && line[1] == 'O')
		ret = parse_texture(0, &line[2], p);
	if (line[0] == 'S' && line[1] == 'O')
		ret = parse_texture(1, &line[2], p);
	if (line[0] == 'W' && line[1] == 'E')
		ret = parse_texture(2, &line[2], p);
	if (line[0] == 'E' && line[1] == 'A')
		ret = parse_texture(3, &line[2], p);
	if (line[0] == 'S' && line[1] != 'O')
		ret = parse_texture(4, &line[2], p);
	if (line[0] == 'F' || line[0] == 'C')
		ret = parse_color(&line[0], p -> color);
	return (ret);
}

void	print_success(t_param *param)
{
	printf("window res = %dx%d \n", param->window->x, param->window->y);
	printf("floor color= %d \n", param->color->floor);
	printf("ceiling = %d \n", param->color->ceiling);
	printf("-------------------\n");
	printf("map size = %dx%d\n", param->map->size.x, param->map->size.y);
	printf("camera starts at %fx%f\n", param->pos.x, param->pos.y);
	printf("-------------------\n");
	int x = 0;
	int y = 0;
	while (y < param->map->size.y)
	{
		while (x < param->map->size.x)
		{
			write(1, &param->map->grid[x][y], 1);
			x++;
		}
		x = 0;
		write(1, "\n", 1);
		y++;
	}
}

t_pt	get_map_dimensions(char *file, char **line, int fd, int offset)
{
	t_pt	dim;
	int		j;

	dim = (t_pt){0, 0};
	j = 0;
	while (*line[0] == '1' || *line[0] == ' ')
	{
		if (dim.x < I(ft_strlen(*line)))
			dim.x = ft_strlen(*line);
		free(*line);
		get_next_line(fd, line);
		dim.y++;
	}
	free(*line);
	close(fd);
	fd = open(file, O_RDONLY);
	get_next_line(fd, line);
	while (j < offset - 1)
	{
		free(*line);
		get_next_line(fd, line);
		j++;
	}
	free(*line);
	return (dim);
}

int	check_and_parse(char **argv, int fd, t_param *param)
{
	char	*line;
	int		offset;

	offset = 0;
	get_next_line(fd, &line);
	while (isvalid(line, param))
	{
		free(line);
		get_next_line(fd, &line);
		offset++;
	}
	param->scrdist = round(param->window->x / 2 / tan((FOV / 2) * RAD));
	param->sizeconst = (float)64 / param->scrdist;
	param->map->size = get_map_dimensions(argv[1], &line, fd, offset);
	if (!(parse_map(fd, line, param)))
		return (0);
	else
		print_success(param);
	return (1);
}
