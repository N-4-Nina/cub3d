/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 10:32:22 by chpl              #+#    #+#             */
/*   Updated: 2020/10/05 22:45:37 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	invalid_cub_file(t_param *p, int code)
{
	p->spritesnb = 0;
	write(1, "Error: \ninvalid .cub file: ", 27);
	if (code == 0)
		write(1, "8 lines must start with correct identifier.", 43);
	if (code == -5)
		write(1, "couldn't parse North texture.", 29);
	if (code == -6)
		write(1, "couldn't parse South texture.", 29);
	if (code == -7)
		write(1, "couldn't parse West texture.", 28);
	if (code == -8)
		write(1, "couldn't parse East texture.", 28);
	if (code == -9)
		write(1, "couldn't parse Sprite texture.", 30);
	if (code == -10)
		write(1, "resolution line is incorrect.", 29);
	if (code == -67)
		write(1, "ceiling color line is incorrect.", 32);
	if (code == -70)
		write(1, "floor color line is incorrect.", 30);
	if (code == -4)
		write(1, "couldn't parse map.", 19);
	free_and_exit(p);
}
