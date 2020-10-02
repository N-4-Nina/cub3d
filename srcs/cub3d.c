/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:06:16 by abouchau          #+#    #+#             */
/*   Updated: 2020/10/02 17:02:15 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_ext(char *s)
{
	int len;

	len = ft_strlen(s) - 1;
	if (s[len] != 'b'
			|| s[len - 1] != 'u'
			|| s[len - 2] != 'c'
			|| s[len - 3] != '.')
		return (0);
	else
		return (1);
}

void	right_args_number(int argc, char **argv, t_param *param)
{
	int	fd;

	if (!(check_ext(argv[1])))
	{
		write(1, "Error: \nFile must have a '.cub' extension.", 41);
		exit(2);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{

		write(1, "Error: \nCub file not found.", 27);
		exit(2);
	}
	if (argc == 2 && argv[1]
			&& !(check_and_parse(argv, fd, param)))
	{
		write(1, "Error: \ninvalid .cub file", 25);
		exit(2);
	}
	else if (argc == 3 && !(ft_strncmp(argv[2], "--save", 6)))
		screenshot(argv, param, fd);

}

void	check_arg(int argc, char **argv, t_param *param)
{
	if (argc == 2 || argc == 3)
		right_args_number(argc, argv, param);
	else
	{
		write(1, "Error: \nInvalid (number of) argument(s).", 39);
		exit(1);
	}
}

void	init_p(t_param *param)
{
	int	i;

	i = 0;
	while (i < 70000)
		param->key[i++] = 0;
	param->map = (t_map *)malloc(sizeof(t_map));
	param->window = (t_window *)malloc(sizeof(t_window));
	param->color = (t_color *)malloc(sizeof(t_color));
	param->dirparsed = 0;
	param->spritesnb = 0;
	param->speed = 0.15;
	param->rotspeed = 0.07;
}

int		main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	t_param	param;

	init_p(&param);
	mlx = mlx_init();
	param.window->mlx = mlx;
	check_arg(argc, argv, &param);
	window = mlx_new_window(mlx, param.window->x, param.window->y, "cub3d");
	param.window->window = window;
	mlx_hook(window, 33, (1 << 8), free_and_exit, &param);
	mlx_hook(window, 2, (1L << 0), keypress, &param);
	mlx_hook(window, 3, (1L << 1), keyrelease, &param);
	mlx_loop_hook(mlx, loop_hook, &param);
	mlx_loop(mlx);
}
