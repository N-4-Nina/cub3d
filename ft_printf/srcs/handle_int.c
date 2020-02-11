/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:31:39 by abouchau          #+#    #+#             */
/*   Updated: 2019/12/20 11:20:15 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"
#include "../libft/libft.h"

int		get_int_size(t_flags argflags, long n)
{
	int		size;

	size = 1;
	if (n == 0 && argflags.isprec == 1 && argflags.precision == 0)
		return (0);
	if (n < 0)
	{
		size++;
		n = -n;
	}
	while (n >= 10)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

void	handle_negative(int i, int fd, t_flags argflags, int *count)
{
	int		prec;
	int		size;
	int		sub;

	size = get_int_size(argflags, i);
	sub = calculate_int_subvalue(argflags, i);
	prec = argflags.precision - size + 1;
	if (!argflags.zeropad && !argflags.minus)
		fill_width(argflags, sub, count);
	write(1, "-", 1);
	handle_prec(prec, count);
	(*count)++;
	if (argflags.zeropad && !argflags.minus)
		fill_width(argflags, sub, count);
	ft_printnbr_fd(i * (-1), fd, 0, count);
	if (argflags.minus)
		fill_width(argflags, sub, count);
}

void	ft_printnbr_fd(long n, int fd, int prec, int *count)
{
	if (n >= 0 && n < 10)
	{
		handle_prec(prec, count);
		ft_putchar_fd(n + 48, fd);
		(*count)++;
	}
	else if (n == -2147483648)
	{
		write(fd, "2147483648", 10);
		(*count) += 10;
	}
	else
	{
		handle_prec(prec, count);
		ft_printnbr_fd(n / 10, fd, 0, count);
		ft_printnbr_fd(n % 10, fd, 0, count);
	}
}

void	write_i(t_flags argflags, va_list arguments, int *count)
{
	int		i;
	int		size;
	int		sub;

	i = va_arg(arguments, int);
	if (argflags.precision == 0 && !argflags.asterprec && !argflags.minwidth &&
			argflags.isprec == 1 && i == 0)
		return ;
	size = get_int_size(argflags, i);
	if (argflags.isprec)
		argflags.zeropad = 0;
	sub = calculate_int_subvalue(argflags, i);
	if (!argflags.minus && i >= 0)
		fill_width(argflags, sub, count);
	if (i < 0)
		handle_negative(i, 1, argflags, count);
	else if (i == 0 && argflags.isprec == 1 && argflags.precision == 0)
		i = 0;
	else
		ft_printnbr_fd(i, 1, argflags.precision - size, count);
	if (argflags.minus && i >= 0)
		fill_width(argflags, sub, count);
}
