/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 12:03:13 by chpl              #+#    #+#             */
/*   Updated: 2020/09/28 10:16:42 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		go_through_line(int indice, char *line, t_map *m, t_param *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'W' || line[i] == 'E')
		{
			m->grid[indice][j] = 48;
			if (!(parse_camera(p, line[i], j, indice)))
				return (0);
			j++;
		}
		else if (line[i] == 48 || line[i] == 49
				|| line[i] == 50 || line[i] == ' ')
			m->grid[indice][j++] = line[i];
		else
			return (-1);
		i++;
	}
	return (j);
}

int		parse_map_line(int indice, char *line, t_map *m, t_param *p)
{
	int j;
	int length;

	length = ft_strlen(line);
	if ((line[0] != 49 && line[0] != ' ') ||
			(line[length - 1] != 49 && (line[length - 1] != ' ')))
		return (0);
	if (!(m->grid[indice] = malloc(m->size.x + 1)))
		return (0);
	if ((j = go_through_line(indice, line, m, p)) == -1)
		return (0);
	while (j < m->size.x)
		m->grid[indice][j++] = 48;
	m->grid[indice][j] = 0;
	return (1);
}

char	**gridswap(char **grid, t_map *m)
{
	char	**grid2;
	int		x;
	int		y;

	x = 0;
	if (!(grid2 = malloc(sizeof(char*) * m->size.x)))
		return (0);
	while (x < m->size.x)
	{
		y = 0;
		grid2[x] = malloc(m->size.y + 1);
		while (y < m->size.y)
		{
			grid2[x][y] = grid[y][x];
			y++;
		}
		grid2[x][y] = 0;
		x++;
	}
	free_tmp_grid(grid, m);
	return (grid2);
}

int		parse_map(int fd, char *line, t_param *p)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (!(p->map->grid = malloc(sizeof(char*) * p->map->size.y)))
		return (0);
	while (get_next_line(fd, &line))
	{
		if (!(parse_map_line(y, line, p->map, p)))
		{
			free(line);
			return (0);
		}
		y++;
		free(line);
	}
	free(line);
	if (!(p->map->grid = gridswap(p->map->grid, p->map))
			|| !(p->dirparsed))
		return (0);
	flood_fill(p, (t_pt){I(p->pos.x - 0.5), I(p->pos.y - 0.5)});
	p->sqx = p->window->x / p->map->size.x;
	p->sqy = p->window->y / p->map->size.y;
	return (1);
}
