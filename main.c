/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:06:16 by abouchau          #+#    #+#             */
/*   Updated: 2020/02/05 17:04:29 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	draw_grid(t_param *p)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;

	int x = p->camera->x*p->window->x/(p->map->sizeX*64); 
	int y = p->camera->y*p->window->y/(p->map->sizeY*64);
	int x1;
	int y1;

	while (j <= p->map->sizeX)
	{
		draw_line((t_pt){i, 0}, (t_pt){i,p->window->x}, 16777215, p);
		i += p->sqx;
		j++;
	}
	i = 0;
	j= 0;
	while (j <= p->map->sizeY)
	{
		draw_line((t_pt){0, i}, (t_pt){p->window->x, i}, 16777215, p);
		i += p-> sqy;
		j++;
	}
	k = -30;
	while (k<30)
	{
		x1 = x - cos((p->camera->direction + k) * 0.0174533)*40;
		y1 = y - sin((p->camera-> direction + k) * 0.0174533)*40;
		draw_line((t_pt){x,y}, (t_pt){x1, y1}, 0xBFFE3E, p);
		k++;
	}
}

int	loop_hook(void *param)
{
	t_param	*p;
	p = (t_param*)param;


	if (p->toggle)
		draw_grid(p);
	cast_rays(p);
	mlx_clear_window(p->window->mlx, p->window->window);
	return (1);
}

int	keycode(int keycode, void *param)
{
	//t_pt	pt;
	//t_pt	pt1;
	t_param	*p;


	p = (t_param*)param;
	/*	pt = (t_pt){0,400};
		pt1 = (t_pt){1280, 400};
		*/
	if (keycode == 53)
		exit(keycode);

	if (keycode == 41)
	{
		if (p->toggle)
			p->toggle = 0;
		else
			p->toggle = 1;
	}
	if (keycode == 126)
		move_cam('z', p);
	if (keycode == 125)
		move_cam('s', p);
	if (keycode == 123)
	{
		turn_cam(-2, p);
		return(keycode);
	}
	if (keycode == 124)
	{
		turn_cam(2, p);
		return(keycode);
	}
	else
		ft_printf("keycode = %d. \n", keycode);
	   return (keycode);
}

void	check_arg(char **argv, t_param *param)
{
	int	fd;

	if (argv[1])
	{
		if (!(fd = open(argv[1], O_RDONLY)))
			exit(2);
		if (!(check_and_parse(argv, fd, param)))
		{
			ft_printf("invalid .cub file");
			exit (2);
		}
	}
	else
	{
		ft_printf("missing arg");
		exit(1);
	}
}
/*
   void	render(t_param *param)
   {
   }
   */

void	init_p(t_param *param)
{
	param->map = (t_map *)malloc(sizeof(t_map));
	param->window = (t_window *)malloc(sizeof(t_window));
	param->texture = (t_texture *)malloc(sizeof(t_texture));
	param->color = (t_color *)malloc(sizeof(t_color));
	param->camera = (t_camera *)malloc(sizeof(t_camera));
	param->toggle = 0;
	ft_printf("init_p finished\n");
}


int	main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	t_param		param;

	//t_window	p_window;
	//param -> window = &p_window;
	argc++;
	init_p(&param);
	check_arg(argv, &param);

	mlx = mlx_init();
	window = mlx_new_window(mlx, param.window -> x, param.window -> y, "cub3d");
	param.window -> mlx = mlx;
	param.window -> window = window;


	mlx_key_hook(window, keycode, &param);
	mlx_loop_hook(mlx, loop_hook, &param);
	mlx_loop(mlx);
}
/*
   cube_size = screenwidth/2;

   w = 13
   a = 0
   s = 1
   d = 2
   */
