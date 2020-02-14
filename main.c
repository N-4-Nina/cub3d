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

int	loop_hook(void *param)
{
	t_pt	pt;
	t_pt	pt1;
	t_param	*p;
	p = (t_param*)param;

	pt = (t_pt){0,400};
	pt1 = (t_pt){1280, 400};
	draw_line(pt, pt1,16777215, param);
	pt = (t_pt){640,0};
	pt1 = (t_pt){640, 400};
	draw_line(pt, pt1,16777215, param);
	pt = (t_pt){960,0};
	pt1 = (t_pt){320,800};
	draw_line(pt, pt1,16777215, param);
	pt = (t_pt){320,0};
	pt1 = (t_pt){960,800};
	draw_line(pt, pt1,16777215, param);
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
	/*
	if (keycode == 124)
	{
		draw_line(pt, pt1,16777215, param);
		pt = (t_pt){640,0};
		pt1 = (t_pt){640, 400};
		draw_line(pt, pt1,16777215, param);
		pt = (t_pt){960,0};
		pt1 = (t_pt){320,800};
		draw_line(pt, pt1,16777215, param);
		pt = (t_pt){320,0};
		pt1 = (t_pt){960,800};
		draw_line(pt, pt1,16777215, param);
	}
	if (keycode == 123)
		mlx_clear_window(p->window->mlx, p->window->window);
		*/
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
	param->floor = (t_floor *)malloc(sizeof(t_floor));
	param->ceiling = (t_ceiling *)malloc(sizeof(t_ceiling));
	param->camera = (t_camera *)malloc(sizeof(t_camera));
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
