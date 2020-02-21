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


#include "../minilibx_opengl_20191021/mlx.h"
//#include "get_next_line.h"
#include "../ft_printf/libft/libft.h"
#include "libftprintf.h"
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>

/*
 * CUB3D STRUCTURES
 */

typedef	struct	s_point
{
	int	x;
	int	y;
}		t_pt;
/*
typedef	struct	s_matrix
{
	int	x;	
}
*/
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
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char	*path_s;
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
	t_texture	*texture;
	t_map		*map;
	int		toggle;
	int		sqx;
	int		sqy;
	int		scrdist;
	int		sizeconst;
}		t_param;

int	ft_atoi(const char *str);

/*
 * GNL_
 */
//int		ft_strlen(const char *str);
//char	*ft_substr(char const *s, int start, int len);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *src);
//int	gnl_write(int fd, char **line, char *still[OPEN_MAX]);
//int	gnl_read(int fd, int check, int ret, char *still[OPEN_MAX]);

	int		check_new_line(char *s);
	int		get_next_line(int fd, char **line);
	/*
	 * CUB3D
	 */
	void	print_success(t_param *param);
	int	check_and_parse(char **argv, int fd, t_param *param);
	int	parse_map_border(int indice, char *line, t_map *m);
	int	parse_map_line(int indice, char *line, t_map *m, t_camera *c);
	int	parse_map(int fd, char *line, t_param *p);
	int	parse_camera(t_camera *c, char dir, char x, char y);

	void	draw_line(t_pt pt, t_pt pt1, int color, t_param *p);

	int	cast_rays(t_param *p);

	void	turn_cam(int i, t_param *p);
	void	move_cam(char d,t_param *p);

#endif
