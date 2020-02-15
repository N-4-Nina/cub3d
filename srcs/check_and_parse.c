/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:11:00 by abouchau          #+#    #+#             */
/*   Updated: 2020/02/05 17:04:28 by abouchau         ###   ########.fr       */
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

int	parse_res(char *line, t_window *param)
{
	param -> x = ft_atoi(line);
	param -> y = ft_atoi(line + int_size(param -> x) + 1);
	if (!(param -> x) || ! (param -> y))
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

int	parse_texture(int id, char *line, t_texture *p)
{
	int	fd;

	while (*line == ' ')
		line++;
	fd = open(line, O_RDONLY);
	if (fd > 1)
	{
		if (id == 1)
			p -> path_no = ft_strdup(line);
		else if (id == 2)
			p -> path_so = ft_strdup(line);
		else if (id == 3)
			p -> path_we = ft_strdup(line);
		else if (id == 4)
			p -> path_ea = ft_strdup(line);
		else if (id == 5)
			p -> path_s = ft_strdup(line);
		close(fd);
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
		ret = parse_res(&line[2], p -> window);
	if (line[0] == 'N' && line[1] == 'O')
		ret = parse_texture(1, &line[2], p -> texture);
	if (line[0] == 'S' && line[1] == 'O')
		ret = parse_texture(2, &line[2], p -> texture);
	if (line[0] == 'W' && line[1] == 'E')
		ret = parse_texture(3, &line[2], p -> texture);
	if (line[0] == 'E' && line[1] == 'A')
		ret = parse_texture(4, &line[2], p -> texture);
	if (line[0] == 'S' && line[1] != 'O')
		ret = parse_texture(5, &line[2], p -> texture);
	if (line[0] == 'F' || line[0] == 'C')
		ret = parse_color(&line[0], p -> color);
	return (ret);
}

int	parse_camera(t_camera *c, char dir, char x, char y)
{
	c -> x = x*64+32;
	c -> y = y*64+32;
	if (dir == 'N')
		c -> direction = 90;
	else if (dir == 'S')
		c -> direction = 270;
	else if (dir == 'E')
		c -> direction = 180;
	else if (dir == 'W')
		c -> direction = 0;
	return (1);
}

void	print_success(t_param *param)
{
	ft_printf("window res = %dx%d \n", param-> window -> x, param -> window -> y);
		ft_printf("floor color= %d \n", param-> color ->floor);
	ft_printf("ceiling = %d \n", param-> color -> ceiling);
	ft_printf("northtextpath= %s\n", param -> texture -> path_no);
	ft_printf("southtextpath= %s\n", param -> texture -> path_so);
	ft_printf("westtextpath= %s\n", param -> texture -> path_we);
	ft_printf("easttextpath= %s\n", param -> texture -> path_ea);
	ft_printf("spritetextpath= %s\n", param -> texture -> path_s);
	ft_printf("-------------------\n");
	ft_printf("map size = %dx%d\n", param -> map -> sizeX, param -> map -> sizeY);
	ft_printf("camera starts at %dx%d facing %d°\n", param -> camera -> x, param -> camera -> y, param -> camera -> direction);
	ft_printf("-------------------\n");
	int i = 0;
	int y = 0;
	while (y <= param -> map -> sizeY)
	{
		while (i < param -> map -> sizeX)
		{
			ft_printf("%c ", param -> map -> grid[y][i]);
			i++;
		}
		i = 0;
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
	param->map->sizeY = get_sizeY(argv[1], &line, fd, offset);
	if (line[0] != '1')
		return (0);
	if (!(parse_map(fd, line, param)))
		return (0);
	else
		print_success(param);
	return (1);
}
