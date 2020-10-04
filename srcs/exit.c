/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 12:12:49 by chpl              #+#    #+#             */
/*   Updated: 2020/10/04 22:31:36 by chpl             ###   ########.fr       */
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

void	free_sprites(t_param *p)
{
	int	i;

	i = 0;
	while (i < p->spritesnb)
	{
		free(p->sprites[i]);
		i++;
	}
	free(p->sprites);
}

void	free_grid(t_param *p)
{
	int	i;

	i = 0;
	if (p->gridparsed)
	{
		while (i < p->map->size.x)
		{
			free(p->map->grid[i]);
			i++;
		}
	}
	else
	{
		while (i < p->linesparsed)
		{
			free(p->map->grid[i]);
			i++;
		}
	}
	if (p->linesparsed || p->gridparsed)
		free(p->map->grid);
}

int		free_and_exit(t_param *p)
{
	int	i;

	i = 0;
	free_grid(p);
	if (p->gridparsed)
		free_sprites(p);
	while (i < 5)
	{
		if (p->tex[i].img != NULL)
			mlx_destroy_image(p->window->mlx, p->tex[i].img);
		i++;
	}
	free(p->map);
	if (p->window->window)
		mlx_destroy_window(p->window->mlx, p->window->window);
	free(p->window->mlx);
	free(p->window);
	free(p->color);
	if (p->wallsdist)
		free(p->wallsdist);
	exit(1);
}
