/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:44:26 by abouchau          #+#    #+#             */
/*   Updated: 2020/09/17 12:49:18 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include "../linux/minilibx-linux/mlx.h"
#include "../osx/minilibx_opengl/mlx.h"
#include "keycodes.h"
//#include "get_next_line.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#include <math.h>
#include <stdio.h>
#include <bits/stdio_lim.h>
# define PI 3.14159265359
# define RAD 0.01745329251
# define FOV 66
# define I (int)
# define FT (float)

/*
 * CUB3D STRUCTURES
 */

typedef	struct	s_point
{
	int	x;
	int	y;
}		t_pt;

typedef	struct	s_floatpoint
{
	double	x;
	double	y;
}		t_fpt;

typedef	struct	s_ray
{
	t_pt	H;
	t_pt	V;
	t_pt	Ha;
	t_pt	Va;

}		t_ray;

typedef	struct	s_linedraw
{
	t_pt	ori;
	t_pt	delta;
	t_pt	delta1;
	t_pt	p;
	t_pt	e;
	int	color;
}		t_linedraw;

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
	int	direction;
}		t_camera;

typedef	struct	s_color
{
	int	ceiling;
	int	floor;
}		t_color;

typedef	struct	s_texture
{
	void	*img;
	void	*ptr;
	int	w;
	int	h;
	int	bpp;
	int	size_line;
	int	endian;
}		t_texture;

typedef	struct	s_map
{
	int	size;
	int	sizeX;
	int	sizeY;
	char	**grid;
}		t_map;

typedef	struct	s_grid
{
	int	sizeX;
	int	sizeY;
}		t_grid;

typedef	struct	s_params
{
	t_window	*window;
	t_camera	*camera;
	t_color		*color;
	t_map		*map;

	t_pt		step;
	t_pt		mappt;
	t_pt		winsize;
	t_pt		scrsize;
	t_pt		texpt;

	void		*frame;
	void		*frameptr;
	t_texture	tex[5];
	t_fpt		pos;
	t_fpt		dir;
	t_fpt		plane;
	t_fpt		raypos;
	t_fpt		raydir;
	t_fpt		sidedist;
	t_fpt		delta;

	int		key[70000];
	int		id;
	int		hit;
	int		side;
	int		x;
	int		height;
	int		top;
	int		bot;
	int		toggle;
	int		sqx;
	int		sqy;
	int		scrdist;
	int			bpp;
	int			endian;
	int			sl;
	float		sizeconst;
	double		x_cam;
	double		x_wall;
	double		walldist;
	double		speed;
	double		rotspeed;
}		t_param;

int	ft_atoi(const char *str);

/*
 * GNL_
 */
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *src);

	int		check_new_line(char *s);
	int		get_next_line(int fd, char **line);
	/*
	 * CUB3D
	 */
	void	print_success(t_param *param);
	int	check_and_parse(char **argv, int fd, t_param *param);
	int	parse_map_border(int indice, char *line, t_map *m);
	int	parse_map_line(int indice, char *line, t_map *m, t_param *p);
	int	parse_map(int fd, char *line, t_param *p);
	int	parse_camera(t_param *p, char dir, int x, int y);

	void	draw_line(t_pt pt, t_pt pt1, int color, t_param *p);
	void	add_slice(int x, int top, int bot, t_param *p);

	void	ray_casting(t_param *p);

	void	turn_cam(int i, t_param *p);
	void	move_cam(t_param *p);

	int	loop_hook(void *param);
	int	keypress(int keycode, void *param);
	int	keyrelease(int keycode, void *param);

	void	check_print(t_param *p);
	void  turn(t_param *p);

	void free_and_exit(t_param *p);

#endif
