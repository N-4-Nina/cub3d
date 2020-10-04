/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 12:08:15 by chpl              #+#    #+#             */
/*   Updated: 2020/10/01 10:34:02 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pxl_to_frame(int x, int y, t_param *p)
{
	if (x < p->window->x && y < p->window->y)
	{
		p->texpt.y = abs((((y * 256 - p->window->y * 128 + p->height * 128)
						* 64) / p->height) / 256);
		ft_memcpy((void *)p->frameptr + 4 * p->window->x * y + x * 4,
				&p->tex[p->orient].ptr[p->texpt.y % 64
				* p->tex[p->orient].size_line +
				p->texpt.x % 64 * p->tex[p->orient].bpp / 8], sizeof(int));
	}
}

void	draw_ceiling(int x, int top, t_param *p)
{
	int	y;

	y = 0;
	while (y < top)
	{
		ft_memcpy((void*)p->frameptr + 4
				* p->window->x * y + x * 4, &p->color->ceiling, sizeof(int));
		y++;
	}
}

void	draw_floor(int x, int bot, t_param *p)
{
	while (bot < p->window->y)
	{
		ft_memcpy((void*)p->frameptr + 4
				* p->window->x * bot + x * 4, &p->color->floor, sizeof(int));
		bot++;
	}
}

void	add_slice(int x, int top, int bot, t_param *p)
{
	p->id = p->map->grid[p->mappt.x][p->mappt.y];
	if (p->side == 0)
		p->x_wall = p->raypos.y + p->walldist * p->raydir.y;
	else
		p->x_wall = p->raypos.x + p->walldist * p->raydir.x;
	p->texpt.x = (int)(p->x_wall * 64.);
	if (p->side == 0 && p->raydir.x > 0)
		p->texpt.x = 64 - p->texpt.x - 1;
	if (p->side == 1 && p->raydir.y < 0)
		p->texpt.x = 64 - p->texpt.x - 1;
	p->texpt.x = abs(p->texpt.x);
	draw_ceiling(x, top + 1, p);
	while (++top <= bot)
		pxl_to_frame(x, top, p);
	draw_floor(x, bot, p);
}
