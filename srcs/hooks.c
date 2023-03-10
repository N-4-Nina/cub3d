/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 12:19:22 by chpl              #+#    #+#             */
/*   Updated: 2020/10/01 18:58:05 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	loop_hook(void *param)
{
	t_param	*p;

	p = (t_param*)param;
	ray_casting(p);
	move_cam(p);
	move_sideways(p);
	turn(p);
	return (1);
}

int	keyrelease(int keycode, void *param)
{
	t_param	*p;

	p = (t_param*)param;
	p->key[keycode] = 0;
	return (keycode);
}

int	keypress(int keycode, void *param)
{
	t_param	*p;

	p = (t_param*)param;
	p->key[keycode] = 1;
	if (keycode == ESCAPE)
		free_and_exit(p);
	return (keycode);
}
