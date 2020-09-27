/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:06:16 by abouchau          #+#    #+#             */
/*   Updated: 2020/09/18 09:38:55 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	check_arg(int argc, char **argv, t_param *param)
{
	int	fd;

	if (argc == 2 && argv[1])
	{
		if (!(fd = open(argv[1], O_RDONLY)))
			exit(2);
		if (!(check_and_parse(argv, fd, param)))
		{
			printf("invalid .cub file");
			exit (2);
		}
	}
	else if (argc == 3 && !(ft_strncmp(argv[2], "--save", 6)))
		screenshot(argv, param);
	else
	{
		write(1, "Invalid (number of) argument(s).", 32);
		exit(1);
	}
}

void	init_p(t_param *param)
{
	param->map = (t_map *)malloc(sizeof(t_map));
	param->window = (t_window *)malloc(sizeof(t_window));
	param->color = (t_color *)malloc(sizeof(t_color));
	param->sprites = (t_sprites **)malloc(sizeof(t_sprites*));
	param->dirparsed = 0;
	param->spritesnb = 0;
	param->speed = 0.15;
	param->rotspeed = 0.07;
	printf("init_p finished\n");
}


int	main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	t_param		param;

	init_p(&param);
	mlx = mlx_init();
	param.window -> mlx = mlx;
	check_arg(argc, argv, &param);

	window = mlx_new_window(mlx, param.window -> x, param.window -> y, "cub3d");
	param.window -> window = window;

	mlx_hook(window, 17, (1<<8), free_and_exit, &param);
	mlx_hook(window, 2, (1L << 0), keypress, &param);
	mlx_hook(window, 3, (1L << 1), keyrelease, &param);
	mlx_loop_hook(mlx, loop_hook, &param);
	mlx_loop(mlx);
}
