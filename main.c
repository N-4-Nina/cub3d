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

	t_param		param;
	t_window	p_window;
	t_texture	textures;
	t_floor		floor;
	t_ceiling	ceiling;


	param.window = &p_window;
	param.texture = &textures;
	param.floor = &floor;
	param.ceiling = &ceiling;
	param.sprite = &sprite;

	if (argv[1])
	{
		if (!(fd = open(argv[1], O_RDONLY)))
			exit(2);
		if (!(check_and_parse(fd, &param)))
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
	window = mlx_new_window(mlx, p_window.x, p_window.y, "cub3d");
	p_window.mlx = mlx;
	p_window.window = window;


	mlx_key_hook(window, draw, &p_window);
	mlx_loop(mlx);
}

/*
 w = 13
 a = 0
 s = 1
 d = 2
 */
