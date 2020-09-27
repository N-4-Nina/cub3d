/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 12:12:49 by chpl              #+#    #+#             */
/*   Updated: 2020/09/27 12:16:41 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_tmp_grid(char **grid, t_map *m)
{
	int	i;

	i = 0;
	while (i < m->size.y)
		free(grid[i++]);
	free(grid);
}

void	free_grid(t_param *p)
{
	int	i;

	i = 0;
	while (i < p->map->size.x)
	{
		free(p->map->grid[i]);
		i++;
	}
	free(p->map->grid);
}

int		free_and_exit(t_param *p)
{
	int	i;

	i = 0;
	free_grid(p);
	while (i < 5)
	{
		mlx_destroy_image(p->window->mlx, p->tex[i].img);
		i++;
	}
	free(p->map);
	free(p->window -> mlx);
	free(p->window);
	free(p->color);
	free(p->sprites);
	exit(1);
}
