/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 12:28:08 by chpl              #+#    #+#             */
/*   Updated: 2020/09/30 10:29:59 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_hit(t_param *p)
{
	if (p->mappt.x < 0. || p->mappt.y < 0.
			|| p->mappt.x >= FT(p->map->size.x)
			|| p->mappt.y >= FT(p->map->size.y))
		return (0);
	if (p->map->grid[p->mappt.x][p->mappt.y] == 49)
		p->hit = 1;
	return (1);
}

void	ray_init(t_param *p, int x)
{
	p->x_cam = 2 * x / (double)(p->window->x) - 1;
	p->raypos.x = p->pos.x;
	p->raypos.y = p->pos.y;
	p->raydir.x = p->dir.x + p->plane.x * p->x_cam;
	p->raydir.y = p->dir.y + p->plane.y * p->x_cam;
	p->mappt.x = I(p->raypos.x);
	p->mappt.y = I(p->raypos.y);
	dda_init(p);
	dda(p);
	if (p->side == 0)
		p->walldist = (p->mappt.x - p->raypos.x +
				(1 - p->step.x) / 2) / p->raydir.x;
	else
		p->walldist = (p->mappt.y - p->raypos.y +
				(1 - p->step.y) / 2) / p->raydir.y;
	p->wallsdist[p->x] = p->walldist;
}

void	wall_height(t_param *p)
{
	p->height = I(p->window->y / p->walldist);
	p->top = -p->height / 2 + p->window->y / 2;
	p->top = (p->top < 0) ? 0 : p->top;
	p->bot = p->height / 2 + p->window->y / 2;
	p->bot = (p->bot < 0) ? 0 : p->bot;
}

void	ray_casting(t_param *p)
{
	p->x = -1;
	p->frame = mlx_new_image(p->window->mlx, p->window->x, p->window->y);
	p->frameptr =
		(unsigned int*)mlx_get_data_addr(p->frame, &p->bpp, &p->sl, &p->endian);
	while (++p->x < p->window->x)
	{
		ray_init(p, p->x);
		wall_height(p);
		add_slice(p->x, p->top - 1, p->bot, p);
	}
	sprites(p);
	mlx_put_image_to_window(p->window->mlx, p->window->window, p->frame, 0, 0);
	mlx_do_sync(p->window->mlx);
	mlx_destroy_image(p->window->mlx, p->frame);
}

void	single_ray_cast(t_param *p)
{
	p->x = -1;
	p->frame = mlx_new_image(p->window->mlx, p->window->x, p->window->y);
	p->frameptr =
		(unsigned int*)mlx_get_data_addr(p->frame, &p->bpp, &p->sl, &p->endian);
	while (++p->x < p->window->x)
	{
		ray_init(p, p->x);
		wall_height(p);
		add_slice(p->x, p->top - 1, p->bot, p);
	}
	sprites(p);
	mlx_destroy_image(p->window->mlx, p->frame);
}
