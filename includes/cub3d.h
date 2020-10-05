/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:44:26 by abouchau          #+#    #+#             */
/*   Updated: 2020/10/05 16:33:20 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../linux/minilibx-linux/mlx.h"
# include "../osx/minilibx_opengl/mlx.h"
# include "keycodes.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>

# define PI 3.14159265359
# define RAD 0.01745329251
# define FOV 66

typedef	struct		s_point
{
	int	x;
	int	y;
}					t_pt;

typedef	struct		s_floatpoint
{
	double	x;
	double	y;
}					t_fpt;

typedef	struct		s_window
{
	void	*mlx;
	void	*window;
	int		x;
	int		y;
}					t_window;

typedef	struct		s_color
{
	int	ceiling;
	int	floor;
}					t_color;

typedef	struct		s_texture
{
	void	*img;
	void	*ptr;
	int		w;
	int		h;
	int		bpp;
	int		size_line;
	int		endian;
}					t_texture;

typedef	struct		s_map
{
	t_pt	size;
	char	**grid;
}					t_map;

typedef struct		s_sprites
{
	t_fpt	coord;
	t_fpt	delta;
	t_fpt	raypos;
	t_fpt	texcoord;
	t_fpt	trans;
	t_pt	dim;
	t_pt	begindraw;
	t_pt	enddraw;
	int		xscreen;
	int		d;
	double	dist;
	double	inv;

}					t_sprites;

typedef	struct		s_params
{
	t_window		*window;
	t_color			*color;
	t_map			*map;
	t_sprites		**sprites;
	t_texture		tex[5];
	void			*frame;
	unsigned	int	*frameptr;
	t_pt			step;
	t_pt			mappt;
	t_pt			winsize;
	t_pt			scrsize;
	t_pt			texpt;
	t_pt			sptexpt;
	t_fpt			pos;
	t_fpt			dir;
	t_fpt			plane;
	t_fpt			raypos;
	t_fpt			raydir;
	t_fpt			sidedist;
	t_fpt			delta;
	char			*still[FOPEN_MAX];
	int				key[70000];
	int				id;
	int				hit;
	int				side;
	int				orient;
	int				x;
	int				height;
	int				top;
	int				bot;
	int				sheight;
	int				stop;
	int				sbot;
	int				spritesnb;
	int				sqx;
	int				sqy;
	int				scrdist;
	int				bpp;
	int				endian;
	int				sl;
	int				dirparsed;
	int				gridparsed;
	int				linesparsed;
	int				resparsed;
	double			sizeconst;
	double			*wallsdist;
	double			angle_dir;
	double			x_cam;
	double			x_wall;
	double			x_sprite;
	double			walldist;
	double			speed;
	double			rotspeed;
}					t_param;

int					ft_atoi(const char *str);

int					check_hit(t_param *p);
int					free_and_exit(t_param *p);
int					get_next_line(char *still[FOPEN_MAX], int fd, char **line);
int					int_size(int nb);
int					is_white_space(char c);
int					convert_color(int rgb[3]);
int					check_and_parse(char **argv, int fd, t_param *param);
int					parse_color(char *line, t_color *color);
int					parse_map_line(int indice,
					char *line, t_map *m, t_param *p);
int					parse_map(int fd, char *line, t_param *p);
int					parse_camera(t_param *p, char dir, int x, int y);
int					loop_hook(void *param);
int					keypress(int keycode, void *param);
int					keyrelease(int keycode, void *param);

void				flood_fill(t_param *p, t_pt coord);
void				invalid_cub_file(t_param *p, int code);
void				add_slice(int x, int top, int bot, t_param *p);
void				ray_casting(t_param *p);
void				dda_init(t_param *p);
void				dda(t_param *p);
void				add_sprite(t_param *p, t_pt coord);
void				draw_sprite(t_param *p, t_sprites *sprite);
void				sprites(t_param *p);
void				turn_cam(int i, t_param *p);
void				move_cam(t_param *p);
void				move_sideways(t_param *p);
void				turn(t_param *p);
void				screenshot(char **argv, t_param *p, int fd);
void				single_ray_cast(t_param *p);
void				free_tmp_grid(char **grid, t_map *p);
void				free_grid(t_param *p);
t_pt				get_map_dimensions(t_param *p, char *file,
				char **line, int *fd);
#endif
