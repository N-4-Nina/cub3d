/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:06:16 by abouchau          #+#    #+#             */
/*   Updated: 2020/02/05 16:22:24 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw(int keycode, void *param)
{
	int	x;
	int	y;
	t_window	*win_param;


	win_param = param;
	x = 0;
	y = 0;
	if (keycode == 53)
		exit(keycode);
	else
		ft_printf("keycode = %d. \n", keycode);
	return (keycode);
}


int	main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	int	fd;
	t_window	win_param;

	if (argv[1])
	{
		if (!(fd = open(argv[1], O_RDONLY)))
			exit(2);
		if (!(check_and_parse(fd, &win_param)))
		{
			ft_printf("invalid .cub file");
			return (2);
		}
	}
	else
	{
		ft_printf("missing arg");
		exit(1);
	}

	mlx = mlx_init();
	window = mlx_new_window(mlx, 800, 640, "cub3d");
	win_param.mlx = mlx;
	win_param.window = window;

	mlx_key_hook(window, draw, &win_param);
	mlx_loop(mlx);
}

/*
 w = 13
 a = 0
 s = 1
 d = 2
 */
