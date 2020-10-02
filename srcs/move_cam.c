/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 12:20:43 by chpl              #+#    #+#             */
/*   Updated: 2020/10/01 19:21:40 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_cam(t_param *p)
{
	if (p->key[FORWARD])
	{
		if (p->map->grid[I(p->pos.x + 2
					* (p->dir.x * p->speed))][I(p->pos.y)] == 79)
			p->pos.x += p->dir.x * p->speed;
		if (p->map->grid[I(p->pos.x)][I(p->pos.y + 2
					* (p->dir.y * p->speed))] == 79)
			p->pos.y += p->dir.y * p->speed;
	}
	if (p->key[BACK])
	{
		if (p->map->grid[I(p->pos.x - 2
					* (p->dir.x * p->speed))][I(p->pos.y)] == 79)
			p->pos.x -= p->dir.x * p->speed;
		if (p->map->grid[I(p->pos.x)][I(p->pos.y - 2
					* (p->dir.y * p->speed))] == 79)
			p->pos.y -= p->dir.y * p->speed;
	}
}

void	move_sideways(t_param *p)
{
	if (p->key[RIGHT])
	{
		if (p->map->grid[I(p->pos.x)]
				[I(p->pos.y - 2 * (p->dir.x * p->speed))] == 79)
			p->pos.y += -p->dir.x * p->speed;
		if (p->map->grid[I(p->pos.x + 2 * (p->dir.y * p->speed))]
				[I(p->pos.y)] == 79)
			p->pos.x += p->dir.y * p->speed;
	}
	if (p->key[LEFT])
	{
		if (p->map->grid[I(p->pos.x)]
				[I(p->pos.y + 2 * (p->dir.x * p->speed))] == 79)
			p->pos.y -= -p->dir.x * p->speed;
		if (p->map->grid[I(p->pos.x - 2 * (p->dir.y * p->speed))]
				[I(p->pos.y)] == 79)
			p->pos.x -= p->dir.y * p->speed;
	}
}

void	turn(t_param *p)
{
	double	old_dirx;
	double	old_planex;
	double	dir;

	old_dirx = p->dir.x;
	old_planex = p->plane.x;
	dir = 0.;
	if ((p->key[LTURN] && p->key[RTURN]))
		return ;
	if (p->key[LTURN])
		dir = 1.;
	if (p->key[RTURN])
		dir = -1.;
	p->dir.x = p->dir.x * cos(dir * 0.1)
		- p->dir.y * sin(dir * 0.1);
	p->dir.y = old_dirx * sin(dir * 0.1)
		+ p->dir.y * cos(dir * 0.1);
	p->plane.x = p->plane.x * cos(dir * 0.1)
		- p->plane.y * sin(dir * 0.1);
	p->plane.y = old_planex * sin(dir * 0.1)
		+ p->plane.y * cos(dir * 0.1);
}
