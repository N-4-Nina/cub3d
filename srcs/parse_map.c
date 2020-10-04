/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 12:03:13 by chpl              #+#    #+#             */
/*   Updated: 2020/10/04 22:41:12 by chpl             ###   ########.fr       */
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
		if (line[i] == 50)
			p->spritesnb++;
		if (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'W' || line[i] == 'E')
		{
			m->grid[indice][j] = 48;
			if (!(parse_camera(p, line[i], j, indice)))
				return (-1);
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
	{
		free(m->grid[indice]);
		if (indice == 0)
			free(m->grid);
		return (0);
	}
	while (j < m->size.x)
		m->grid[indice][j++] = 48;
	m->grid[indice][j] = 0;
	return (1);
}

char	**gridswap(t_param *p, char **grid, t_map *m)
{
	char	**grid2;
	int		x;
	int		y;

	x = 0;
	p->sprites = malloc(sizeof(t_sprites*) * p->spritesnb);
	p->spritesnb = 0;
	if (!(grid2 = malloc(sizeof(char*) * m->size.x)))
		return (0);
	while (x < m->size.x)
	{
		y = 0;
		grid2[x] = malloc(m->size.y + 1);
		while (y < m->size.y)
		{
			grid2[x][y] = grid[y][x];
			if (grid2[x][y] == 50)
				add_sprite(p, (t_pt){x, y});
			y++;
		}
		grid2[x][y] = 0;
		x++;
	}
	free_grid(p);
	return (grid2);
}

t_pt	get_map_dimensions(char *file, char **line, int fd, int offset)
{
	t_pt	dim;
	int		j;

	dim = (t_pt){0, 0};
	j = 0;
	while (*line[0] == '1' || *line[0] == ' ')
	{
		if (dim.x < (int)(ft_strlen(*line)))
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

int		parse_map(int fd, char *line, t_param *p)
{
	int	i;

	i = 0;
	if (!(p->map->grid = malloc(sizeof(char*) * p->map->size.y)))
		return (0);
	while (get_next_line(fd, &line))
	{
		if (!(parse_map_line(p->linesparsed, line, p->map, p)))
		{
			free(line);
			return (0);
		}
		p->linesparsed++;
		free(line);
	}
	free(line);
	if (!(p->map->grid = gridswap(p, p->map->grid, p->map))
			|| !(p->dirparsed))
		return (0);
	flood_fill(p, (t_pt){(int)(p->pos.x - 0.5), (int)(p->pos.y - 0.5)});
	p->sqx = p->window->x / p->map->size.x;
	p->sqy = p->window->y / p->map->size.y;
	return (1);
}
