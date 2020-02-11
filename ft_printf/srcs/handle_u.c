/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:34:44 by abouchau          #+#    #+#             */
/*   Updated: 2019/12/16 14:10:49 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"
#include "../libft/libft.h"

int		get_unsize(t_flags argflags, unsigned int n)
{
	int		size;

	size = 1;
	if (n == 0 && argflags.isprec == 1 && argflags.precision == 0)
		return (0);
	while (n >= 10)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

void	ft_printunsigned_fd(unsigned int n, int fd, int prec, int *count)
{
	if (n < 10)
	{
		handle_prec(prec, count);
		ft_putchar_fd(n + 48, fd);
		(*count)++;
	}
	else
	{
		handle_prec(prec, count);
		ft_printunsigned_fd(n / 10, fd, 0, count);
		ft_printunsigned_fd(n % 10, fd, 0, count);
	}
}

void	write_u(t_flags argflags, va_list arguments, int *count)
{
	unsigned	int		u;
	int					size;
	int					sub;

	u = va_arg(arguments, unsigned int);
	if (argflags.precision == 0 && argflags.isprec == 1 &&
			!argflags.minwidth && u == 0)
		return ;
	size = get_unsize(argflags, u);
	sub = calculate_unsigned_subvalue(argflags, u);
	if (!argflags.minus)
		fill_width(argflags, sub, count);
	if (u == 0 && argflags.isprec == 1 && argflags.precision == 0)
		u = 0;
	else
		ft_printunsigned_fd(u, 1, argflags.precision - size, count);
	if (argflags.minus)
		fill_width(argflags, sub, count);
}
