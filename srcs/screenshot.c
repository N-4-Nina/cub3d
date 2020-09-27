/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 12:36:32 by chpl              #+#    #+#             */
/*   Updated: 2020/09/27 12:54:41 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	shift(unsigned char *headers, int value)
{
	headers[0] = UC(value);
	headers[1] = UC(value >> 8);
	headers[2] = UC(value >> 16);
	headers[3] = UC(value >> 24);
}

void	write_headers(int fd, t_param *p, int size)
{
	unsigned	char	headers[54];
	int					i;

	i = 0;
	while (i < 54)
		headers[i++] = UC(0);
	headers[0] = UC('B');
	headers[1] = UC('M');
	shift(headers + 2, size);
	headers[10] = UC(54);
	headers[14] = UC(40);
	shift(headers + 18, p->window->x);
	shift(headers + 22, p->window->y);
	headers[27] = UC(1);
	headers[28] = UC(24);
	write(fd, headers, 54);
}

int		write_colors(int fd, t_param *p, t_pt dim)
{
	static	unsigned	char	rgb[3] = {
		0, 0, 0 };
	int							i;
	int							j;

	i = 0;
	while (i < p->window->y)
	{
		j = 0;
		while (j < p->window->x)
		{
			rgb[0] = ((p->frameptr[(dim.y - i) * dim.x + j]) >> 16);
			rgb[1] = ((p->frameptr[(dim.y - i) * dim.x + j]) >> 8);
			rgb[2] = (p->frameptr[(dim.y - i) * dim.x + j]);
			if ((write(fd, rgb + 2, 1)) < 0)
				return (0);
			if ((write(fd, rgb + 1, 1)) < 0)
				return (0);
			if ((write(fd, rgb, 1)) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	write_image(t_param *p)
{
	int		outputfd;
	int		filesize;
	t_pt	dim;

	filesize = 54 + (p->window->x * p->window->y);
	if (!(outputfd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777)))
		printf("couldn't create bmp\n");
	dim = (t_pt){p->window->x, p->window->y - 1};
	write_headers(outputfd, p, filesize, dim);
	write_colors(outputfd, p);
	close(outputfd);
}

void	screenshot(char **argv, t_param *p)
{
	int fd;

	if (!(fd = open(argv[1], O_RDONLY)))
		exit(2);
	if (!(check_and_parse(argv, fd, p)))
	{
		printf("invalid .cub file");
		exit(2);
	}
	single_ray_cast(p);
	write_image(p);
	free_and_exit(p);
}
