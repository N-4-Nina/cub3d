/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 14:06:16 by abouchau          #+#    #+#             */
/*   Updated: 2020/10/05 16:50:19 by chpl             ###   ########.fr       */
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
	int	ret;

	if (!(check_ext(argv[1])))
	{
		write(1, "Error: File must have a '.cub' extension.\n", 41);
		exit(2);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		write(1, "Error: Cub file not found.\n", 27);
		exit(2);
	}
	if (argc == 2 && argv[1]
			&& (ret = (check_and_parse(argv, fd, param))) < 0)
		invalid_cub_file(param, ret);
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
	i = 0;
	while (i < 5)
		param->tex[i++].img = NULL;
	i = 0;
	while (i < FOPEN_MAX)
		param->still[i++] = NULL;
	param->wallsdist = NULL;
	param->map = (t_map *)malloc(sizeof(t_map));
	param->window = (t_window *)malloc(sizeof(t_window));
	param->color = (t_color *)malloc(sizeof(t_color));
	param->window->window = NULL;
	param->dirparsed = 0;
	param->resparsed = 0;
	param->gridparsed = 0;
	param->spritesnb = 0;
	param->linesparsed = 0;
	param->speed = 0.15;
	param->rotspeed = 0.07;
}

int		main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	t_param	p;

	init_p(&p);
	mlx = mlx_init();
	p.window->mlx = mlx;
	check_arg(argc, argv, &p);
	window = mlx_new_window(mlx, p.window->x, p.window->y, "cub3d");
	p.window->window = window;
	mlx_hook(window, 33, (1 << 8), free_and_exit, &p);
	mlx_hook(window, 2, (1L << 0), keypress, &p);
	mlx_hook(window, 3, (1L << 1), keyrelease, &p);
	mlx_loop_hook(mlx, loop_hook, &p);
	mlx_loop(mlx);
}
