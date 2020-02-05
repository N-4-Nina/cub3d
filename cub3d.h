/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:44:26 by abouchau          #+#    #+#             */
/*   Updated: 2020/02/05 16:22:18 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include "minilibx_opengl_20191021/mlx.h"
#include "get_next_line/get_next_line.h"
#include "ft_printf/includes/libftprintf.h"
#include <stdlib.h>
#include <fcntl.h>

typedef	struct	s_window
{
	void	*mlx;
	void	*window;
	int	x;
	int	y;
}		t_window;

typedef	struct	s_camera
{
	int	x;
	int	y;
}		t_camera;

typedef	struct	s_map
{
	int	size;
	int	sizeX;
	int	sizeY;
}		t_map;

int	ft_atoi(const char *str);

int	get_next_line(int fd, char **line);

int	check_and_parse(int fd, t_window *win_param);

#endif
