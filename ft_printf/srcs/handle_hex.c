/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:55:14 by abouchau          #+#    #+#             */
/*   Updated: 2019/12/16 13:15:24 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

void	write_x(t_flags argflags, va_list arguments, int *count)
{
	int		x;
	int		nsize;
	int		sub;
	int		subprec;

	x = va_arg(arguments, long);
	if (argflags.isprec == 1 && !argflags.minwidth
			&& argflags.precision == 0 && x == 0)
		return ;
	nsize = get_hex_size(argflags, x);
	sub = calculate_hex_subvalue(argflags, x);
	subprec = (x < 0) ? 8 : nsize;
	if (!argflags.minus)
		fill_width(argflags, sub, count);
	handle_prec(argflags.precision - subprec, count);
	subprec = 0;
	if (x < 0)
		ft_printnegahexa((long)(x * -1), argflags, count, &subprec);
	else if (x == 0 && argflags.isprec == 1 && argflags.precision == 0)
		x = 0;
	else
		ft_printhexa((long)x, 1, argflags, count);
	if (argflags.minus)
		fill_width(argflags, sub, count);
}

int		get_hex_size(t_flags argflags, long n)
{
	int		i;

	i = 1;
	if (n == -2147483648)
		return (8);
	if (n < 0)
		n = -n;
	if (n == 0 && argflags.isprec == 1 && argflags.precision == 0)
		return (0);
	while (n / 16 != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

void	ft_printhexa(long n, int fd, t_flags argflags, int *count)
{
	char	*base;
	char	towrite;

	base = ft_strdup("0123456789abcdef");
	if (n >= 0 && n < 16)
	{
		towrite = base[n];
		if (n > 9 && n <= 15 && argflags.conversion == 88)
			towrite -= 32;
		write(fd, &towrite, 1);
		(*count)++;
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		(*count)++;
		ft_printhexa(n * (-1), fd, argflags, count);
	}
	else
	{
		ft_printhexa(n / 16, fd, argflags, count);
		ft_printhexa(n % 16, fd, argflags, count);
	}
	free(base);
}
