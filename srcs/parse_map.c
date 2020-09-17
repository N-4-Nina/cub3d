#include "../includes/cub3d.h"

/*
int	parse_map_border(int indice, char *line, t_map *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	m->grid[indice] = malloc(m->sizeX + 1);
	while (line[i])
	{
		if (line[i] == 49)
		{
			m -> grid[indice][j] = 49;
			j++;
		}
		else if (line[i] != 49 && line[i] != ' ')
		{
			free(m->grid[indice]);
			return (0);
		}
		i++;
	}
	m -> grid[indice][j] = 0;
	if (indice != 0)
		m -> sizeY = indice;
	if (line[i] == 0)
		return (1);
	else
		return (0);
}
*/

int	parse_map_line(int indice, char *line, t_map *m, t_param *p)
{
	int	i;
	int	j;
	int length;

	i = 0;
	j = 0;

	length = ft_strlen(line);
	if ((line[0] != 49 && line[0] != ' ') || (line[length - 1] != 49 && (line[length - 1] != ' ')))
		return (0);

	m->grid[indice] = malloc(m -> size.x);
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'W' || line[i] == 'E')
		{
			m -> grid[indice][j] = 48;
			if (!(parse_camera(p, line[i], j, indice)))
				return (0);
			j++;
		}
		if (line[i] == ' ')
			{
				m -> grid[indice][j] = 48;
				j++;
			}
		if (line[i] == 48 || line[i] == 49 || line[i] == 50)
		{
			m -> grid[indice][j] = line[i];
			j++;
		}
		i++;
	}
	while(j < m->size.x)
		m->grid[indice][j++] = 48;
	m -> grid[indice][j] = 0;
	return (1);
}


char	**gridswap(char **grid, t_map *m)
{
	char	**grid2;
	int	x;
	int	y;

	x = 0;
	grid2 = malloc(sizeof(char*) * m->size.x);
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
	free(grid);
	return (grid2);
}


int	parse_map(int fd, char *line, t_param *p)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	p -> map -> grid = malloc(sizeof(char*) * p->map->size.y);
	while (get_next_line(fd, &line))
	{
		if (!(parse_map_line(y, line, p -> map, p)))
		{
				free(line);
				return (0);
		}
		y++;
		free(line);
	}
	p->map->grid = gridswap(p->map->grid, p->map);
	p->sqx = p->window->x/p->map->size.x;
	p->sqy = p->window->y/p->map->size.y;
	return (1);
}
