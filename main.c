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

void	check_print(t_param *p)
{
	printf("position   x: %f, y : %f\n", p->pos.x, p->pos.y);
	printf("direction : %i\n", p->camera->direction);
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

void	init_p(t_param *param)
{
	param->map = (t_map *)malloc(sizeof(t_map));
	param->window = (t_window *)malloc(sizeof(t_window));
	param->color = (t_color *)malloc(sizeof(t_color));
	param->camera = (t_camera *)malloc(sizeof(t_camera));
	param->toggle = 0;
	param->speed = 0.15;
	param->rotspeed = 0.07;
	ft_printf("init_p finished\n");
}


int	main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	t_param		param;

	argc++;
	init_p(&param);
	mlx = mlx_init();
	param.window -> mlx = mlx;
	check_arg(argv, &param);

	window = mlx_new_window(mlx, param.window -> x, param.window -> y, "cub3d");
	param.window -> window = window;

	mlx_hook(window, 2, (1L << 0), keypress, &param);
	mlx_hook(window, 3, (1L << 1), keyrelease, &param);
	mlx_loop_hook(mlx, loop_hook, &param);
	mlx_loop(mlx);
}
