/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 12:20:43 by chpl              #+#    #+#             */
/*   Updated: 2020/09/27 12:26:13 by chpl             ###   ########.fr       */
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

void	turn(t_param *p)
{
	double old_dirx;
	double old_planex;

	old_dirx = p->dir.x;
	old_planex = p->plane.x;
	if (p->key[LTURN])
	{
		old_dirx = p->dir.x;
		p->dir.x = p->dir.x * cos(-p->rotspeed) - p->dir.y * sin(-p->rotspeed);
		p->dir.y = old_dirx * sin(-p->rotspeed) + p->dir.y * cos(-p->rotspeed);
		old_planex = p->plane.x;
		p->plane.x = p->plane.x * cos(-p->rotspeed)
			- p->plane.y * sin(-p->rotspeed);
		p->plane.y = old_planex * sin(-p->rotspeed)
			+ p->plane.y * cos(-p->rotspeed);
	}
	if (p->key[RTURN])
	{
		p->dir.x = p->dir.x * cos(p->rotspeed) - p->dir.y * sin(p->rotspeed);
		p->dir.y = old_dirx * sin(p->rotspeed) + p->dir.y * cos(p->rotspeed);
		p->plane.x = p->plane.x * cos(p->rotspeed)
			- p->plane.y * sin(p->rotspeed);
		p->plane.y = old_planex * sin(p->rotspeed)
			+ p->plane.y * cos(p->rotspeed);
	}
}
