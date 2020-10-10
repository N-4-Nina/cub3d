/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:36:29 by chpl              #+#    #+#             */
/*   Updated: 2020/10/10 10:08:59 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	bubble_sort(t_param *p)
{
	int			i;
	int			j;
	t_sprites	*tmp;

	i = 0;
	while (i < p->spritesnb - 1)
	{
		j = i + 1;
		while (j < p->spritesnb)
		{
			if (p->sprites[i]->dist < p->sprites[j]->dist)
			{
				tmp = p->sprites[i];
				p->sprites[i] = p->sprites[j];
				p->sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	add_slice_sprite(t_param *p, t_sprites *sprite, int x)
{
	int	y;

	y = sprite->begindraw.y;
	while (y < sprite->enddraw.y &&
			sprite->trans.y > 0 && sprite->trans.y < p->wallsdist[x])
	{
		sprite->d = y * 256 - p->window->y * 128 + sprite->dim.y * 128;
		sprite->texcoord.y = ((sprite->d * 64) / sprite->dim.y) / 256;
		if (sprite->texcoord.y < 0)
			sprite->texcoord.y = 0;
		if (*(int *)&p->tex[4].ptr[(int)(sprite->texcoord.y) % 64
				* p->tex[4].size_line + (int)(sprite->texcoord.x) % 64
				* p->tex[4].bpp / 8] != 0x000000)
		{
			ft_memcpy((void*)p->frameptr + 4 * p->window->x * y + x * 4,
					&p->tex[4].ptr[(int)(sprite->texcoord.y) % 64
					* p->tex[4].size_line + (int)(sprite->texcoord.x) % 64
					* p->tex[4].bpp / 8], sizeof(int));
		}
		y++;
	}
}

void	draw_sprite(t_param *p, t_sprites *sprite)
{
	int				x;

	x = sprite->begindraw.x;
	while (x < sprite->enddraw.x)
	{
		sprite->texcoord.x =
			(int)((256 * (x - (-sprite->dim.x / 2 + sprite->xscreen))
						* 64 / sprite->dim.x) / 256);
		if (sprite->texcoord.x < 0)
			sprite->texcoord.x = 0;
		add_slice_sprite(p, sprite, x);
		x++;
	}
}

void	position_sprite(t_param *p, t_sprites *sprite)
{
	sprite->delta.x = sprite->coord.x - p->pos.x;
	sprite->delta.y = sprite->coord.y - p->pos.y;
	sprite->inv = 1.0 / (p->plane.x * p->dir.y -
			p->dir.x * p->plane.y);
	sprite->trans.x = sprite->inv * (p->dir.y * sprite->delta.x -
			p->dir.x * sprite->delta.y);
	sprite->trans.y = sprite->inv * (-p->plane.y * sprite->delta.x +
			p->plane.x * sprite->delta.y);
	sprite->xscreen = (int)((p->window->x / 2) * (1 + sprite->trans.x /
				sprite->trans.y));
	sprite->dim.y = abs((int)(p->window->y / (sprite->trans.y)));
	sprite->begindraw.y = -sprite->dim.y / 2 + p->window->y / 2;
	if (sprite->begindraw.y < 0)
		sprite->begindraw.y = 0;
	sprite->enddraw.y = sprite->dim.y / 2 + p->window->y / 2;
	if (sprite->enddraw.y >= p->window->y)
		sprite->enddraw.y = p->window->y - 1;
	sprite->dim.x = abs((int)(p->window->x / (sprite->trans.y)));
	sprite->begindraw.x = -sprite->dim.x / 2 + sprite->xscreen;
	if (sprite->begindraw.x < 0)
		sprite->begindraw.x = 0;
	sprite->enddraw.x = sprite->dim.x / 2 + sprite->xscreen;
	if (sprite->enddraw.x >= p->window->x)
		sprite->enddraw.x = p->window->x - 1;
}

void	sprites(t_param *p)
{
	int		i;
	double	ori_dir;

	i = 0;
	ori_dir = hypot(p->dir.x, p->dir.y);
	if (p->dir.y >= 0)
		p->angle_dir = acos(p->dir.x / ori_dir) * 180 / PI;
	else
		p->angle_dir = 360 - acos(p->dir.x / ori_dir) * 180 / PI;
	while (i < p->spritesnb)
	{
		p->sprites[i]->dist = hypot(p->sprites[i]->coord.x - p->pos.x,
				p->sprites[i]->coord.y - p->pos.y);
		i++;
	}
	bubble_sort(p);
	i = 0;
	while (i < p->spritesnb)
	{
		position_sprite(p, p->sprites[i]);
		draw_sprite(p, p->sprites[i]);
		i++;
	}
}
