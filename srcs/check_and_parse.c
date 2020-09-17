/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:11:00 by abouchau          #+#    #+#             */
/*   Updated: 2020/09/17 12:55:11 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	int_size(int nb)
{
	int i;

	i  = 1;
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

	p -> window -> x = ft_atoi(line);
	p -> window -> y = ft_atoi(line + int_size(p-> window -> x) + 1);
	
	mlx_get_screen_size(p->window->mlx, &x, &y);
	if (p -> window -> x > x)
		p -> window -> x = x;
	if (p-> window -> y > y)
		p -> window -> y = y;
		
	if (!(p -> window -> x) || ! (p -> window -> y))
		return (0);
	return (1);
}

int	parse_color(char *line, t_color *color)
{
	int	R;
	int	G;
	int	B;
	int	convert;

	R = ft_atoi(&line[2]);
	G = ft_atoi(&line[2] + int_size(R) + 1);
	B = ft_atoi(&line[2] + int_size(R) + int_size(G) + 2);
	convert = R;
	convert = (convert << 8) + G;
	convert = (convert << 8) + B;
	if (line[0] == 'F')
		color -> floor = convert;
	else if (line[0] == 'C')
		color -> ceiling = convert;
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
		//p->tex[id].img = mlx_new_image(p->window->mlx, 64, 64);
		//p->tex[id].path = ft_strdup(line);
		p->tex[id].img = mlx_xpm_file_to_image(p->window->mlx, line, &p->tex[id].w, &p->tex[id].h);
		p -> tex[id].ptr = mlx_get_data_addr(p->tex[id].img, &p->tex[id].bpp, &p->tex[id].size_line, &p->tex[id].endian);
		printf("parsed texture: %s; \n bpp: %d, sizeline: %d, endian: %d\n", line, p->tex[id].bpp, p->tex[id].size_line, p->tex[id].endian);
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

int	parse_camera(t_param *p, char dir, int x, int y)
{
	p->pos.x = FT(x) + 0.5;
	p->pos.y = FT(y) + 0.5;

	if (dir == 'N')
	{
		p->dir.x = 0;
		p->dir.y = -1;
		p -> plane.x = 0.66;
		p->plane.y = 0;
	}
	else if (dir == 'S')
	{
		p->dir.x = 0;
		p->dir.y = 1;
		p -> plane.x = -0.66;
		p->plane.y = 0;
	}
	else if (dir == 'E')
	{
		p -> dir.x = 1;
		p -> dir.y = 0;
		p -> plane.x = 0;
		p->plane.y = -0.66;
	}
	else if (dir == 'W')
	{
		p -> dir.x = -1;
		p -> dir.y = 0;
		p -> plane.x = 0;
		p->plane.y = 0.66;
	}
	//p -> dir.x = cos(p->camera->direction * RAD);
	//p -> dir.y = sin(p->camera->direction * RAD);
	return (1);
}

void	print_success(t_param *param)
{
	printf("window res = %dx%d \n", param-> window -> x, param -> window -> y);
		printf("floor color= %d \n", param-> color ->floor);
	printf("ceiling = %d \n", param-> color -> ceiling);
	printf("-------------------\n");
	printf("map size = %dx%d\n", param -> map -> sizeX, param -> map -> sizeY);
	printf("camera starts at %fx%f facing %d°\n", param-> pos.x, param -> pos.y, param -> camera -> direction);
	printf("-------------------\n");
	int x = 0;
	int y = 0;
	while (y <= param -> map -> sizeY)
	{
		while (x < param -> map -> sizeX)
		{
			printf("%c ", param -> map -> grid[x][y]);
			x++;
		}
		x = 0;
		write(1, "\n", 1);
		y++;
	}
}

int	get_sizeY(char *file, char **line, int fd, int offset)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*line[0] == '1')
	{
		free(*line);
		get_next_line(fd, line);
		i++;
	}
	free(*line);
	close(fd);
	fd = open(file, O_RDONLY);
	get_next_line(fd, line);
	while (j < offset-1)
	{
		free(*line);
		get_next_line(fd, line);
		j++;
	}
	return (i);
}

int	check_and_parse(char **argv, int fd, t_param *param)
{
	char	*line;
	int	offset;

	offset = 1;
	get_next_line(fd, &line);
	while (isvalid(line, param))
	{
		free(line);
		get_next_line(fd, &line);
		offset++;
	}
	param->scrdist = round(param->window->x/2 / tan((FOV/2) * RAD));
	param->sizeconst = (float)64/param->scrdist;
	param->map->sizeY = get_sizeY(argv[1], &line, fd, offset);
	if (line[0] != '1')
		return (0);
	if (!(parse_map(fd, line, param)))
		return (0);
	else
		print_success(param);
	return (1);
}
