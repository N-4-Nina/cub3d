/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:11:00 by abouchau          #+#    #+#             */
/*   Updated: 2020/02/05 16:22:22 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	int_size(int nb)
{
	int i;

	i  = 1;
	while (nb / 10 != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	handle_map(fd)
{
	return (1);
}

int	check_and_parse(int fd, t_window *win_param)
{
	char	*line;

	get_next_line(fd, &line);
	if (line[0] != 82)
		exit(2);
	win_param -> x = ft_atoi(line + 1);
	win_param -> y = ft_atoi(line + int_size(win_param -> x) + 1);
	ft_printf("x = %d, y = %d \n", win_param -> x, win_param -> y);
	return (1);
}
