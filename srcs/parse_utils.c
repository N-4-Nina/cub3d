/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 12:05:08 by chpl              #+#    #+#             */
/*   Updated: 2020/10/02 13:12:17 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_white_space(char c)
{
	return (c == 32 || (c > 8 && c < 14 && c != '\n'));
}

void	add_sprite(t_param *p, t_pt coord)
{
	int i;

	i = p->spritesnb;
	if (!(p->sprites[i] = (t_sprites *)malloc(sizeof(t_sprites))))
		return ;
	p->sprites[i]->coord = (t_fpt){coord.x + 0.5, coord.y + 0.5};
	p->sprites[i]->raypos = p->raypos;
	p->spritesnb++;
}

int		int_size(int nb)
{
	int i;

	i = 1;
	while (nb / 10 != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}
