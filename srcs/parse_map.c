#include "../includes/cub3d.h"

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

int	parse_map_line(int indice, char *line, t_map *m, t_param *p)
{
	int	i;
	int	j;

	i= 0;
	j = 0;
	if (line[0] != 49 || line[ft_strlen(line) - 1] != 49 || indice == m->sizeY - 1)
		return (0);
	m->grid[indice] = malloc(m->sizeX + 1);
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'W' || line[i] == 'E')
		{
			m -> grid[indice][j] = 48;
			parse_camera(p, line[i], j, indice);
			j++;
		}
		if (line[i] == 48 || line[i] == 49 || line[i] == 50)
		{
			m -> grid[indice][j] = line[i];
			j++;
		}
		i++;
	}
	m -> grid[indice][j] = 0;
	return (1);
}

char	**gridswap(char **grid, t_map *m)
{
	char	**grid2;
	int	x;
	int	y;

	x = 0;
	grid2 = malloc(sizeof(char*) * m->sizeX);
	while (x < m->sizeX)
	{
		y = 0;
		grid2[x] = malloc(m->sizeY + 1);
		while (y <= m->sizeY)
		{
			grid2[x][y] = grid[y][x];
			y++;
		}
		//grid2[x][y] = 0;
		x++;
	}
	free(grid);
	return (grid2);

}

int	get_sizeX(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			j++;
		i++;
	}
	return (j);
}

int	parse_map(int fd, char *line, t_param *p)
{
	int	i;
	int	y;

	i = 0;
	y = 1;
	p -> map -> sizeX = get_sizeX(line);
	p -> map -> grid = malloc(sizeof(char*) * p->map->sizeY);
	if (!(parse_map_border(0, line, p -> map)))
		return (0);
	while (get_next_line(fd, &line))
	{
		if (!(parse_map_line(y, line, p -> map, p)))
		{
			if (!(parse_map_border(y, line, p -> map)))
			{
				free(line);
				return (0);
			}
		}
		y++;
		free(line);
	}
	p->map->grid = gridswap(p->map->grid, p->map);
	p->sqx = p->window->x/p->map->sizeX;
	p->sqy = p->window->y/p->map->sizeY;
	return (1);
}
