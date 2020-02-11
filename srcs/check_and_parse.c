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

int	handle_map(fd)
{
	return (1);
}
int	parse_res(char *line, t_window *param)
{
	param -> x = ft_atoi(line);
	param -> y = ft_atoi(line + int_size(param -> x) + 1);
	if (!(param -> x) || ! (param -> y))
		return (0);
	return (1);
}

int	parse_floor(char *line, t_floor *floor)
{
	int i;

	i = 0;
	floor -> R = ft_atoi(line);
	floor -> G = ft_atoi(line + int_size(floor -> R) + 1);
	floor -> B = ft_atoi(line + int_size(floor -> R) + int_size(floor -> G) + 2);
	return (1);
}

int	parse_ceiling(char *line, t_ceiling *ceiling)
{
	int i;

	i = 0;
	ceiling -> R = ft_atoi(line);
	ceiling -> G = ft_atoi(line + int_size(ceiling -> R) + 1);
	ceiling -> B = ft_atoi(line + int_size(ceiling -> R) + int_size(ceiling -> G) + 2);
	return (1);
}
int	parse_texture(char *line, t_texture *texture)
{
	int	i;
	int	fd;

	while (line[i] == ' ')
		i++;
	if ((fd = open(line+i, O_RDONLY)))
	{
		i--;
		texture -> path = ft_strdup(&line[i]);
		close(fd);
		return (1);
	}
	else
		return (0);
}

int	isvalid(char *line, t_param *param)
{
	int	ret;

	ret = 0;
	if (line[0] == 'R')
		ret = parse_res(&line[2], param -> window);
	if (line[0] == 'N' && line[1] == 'O')
		ret = parse_texture(&line[3], param -> north);
	if (line[0] == 'S' && line[1] == 'O')
		ret = parse_texture(&line[3], param -> west);
	if (line[0] == 'W' && line[1] == 'E')
		ret = parse_texture(&line[3], param -> east);
	if (line[0] == 'E' && line[1] == 'A')
		ret = parse_texture(&line[3], param -> south);
	if (line[0] == 'S' && line[1] != 'O')
		ret = parse_texture(&line[2], param -> sprite);
	if (line[0] == 'F')
		ret = parse_floor(&line[2], param -> floor);
	if (line[0] == 'C')
		ret = parse_ceiling(&line[2], param -> ceiling);
	return (ret);
}

int	check_and_parse(int fd, t_param *param)
{
	char	*line;

	get_next_line(fd, &line);
	while (isvalid(line, param))
	{
		//ft_printf("%s\n", line);
		free(line);
		get_next_line(fd, &line);
	}
	if (line[0] != '1')
		return (0);
	//get_next_line(fd, &line);
	ft_printf("window res = %dx%d \n", param-> window -> x, param -> window -> y);
	ft_printf("floor = R%d G%d B%d \n", param-> floor -> R, param -> floor -> G, param -> floor -> B);
	ft_printf("ceiling = R%d G%d B%d \n", param-> ceiling -> R, param -> ceiling -> G, param -> ceiling -> B);
	ft_printf("textures = north%s south% swest%s east%s \n", param -> north -> path, param -> south -> path, param -> west -> path, param -> east -> path);
	return (1);
}
