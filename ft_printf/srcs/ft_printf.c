/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:44:37 by abouchau          #+#    #+#             */
/*   Updated: 2019/11/27 11:50:35 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

int	dispatch(t_flags argflags, va_list arguments, int *count)
{
	if (argflags.conversion == 'c')
		write_c(argflags, arguments, count);
	if (argflags.conversion == '%')
		write_percent(argflags, count);
	if (argflags.conversion == 's')
		write_s(argflags, arguments, count);
	if (argflags.conversion == 'p')
		write_p(argflags, arguments, count);
	if (argflags.conversion == 'd' || argflags.conversion == 'i')
		write_i(argflags, arguments, count);
	if (argflags.conversion == 'u')
		write_u(argflags, arguments, count);
	if (argflags.conversion == 'x' || argflags.conversion == 'X')
		write_x(argflags, arguments, count);
	return (0);
}

int	go_through(const char *format, va_list arguments, int *count)
{
	int i;
	int arg_nbr;

	i = -1;
	arg_nbr = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			dispatch(handle_arg(arguments, &format[i + 1]), arguments, count);
			i++;
			while (!(isconvchar(format[i])))
				i++;
		}
		else if (format[i] != '%')
		{
			write(1, &format[i], 1);
			(*count)++;
		}
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	arguments;

	i = 0;
	va_start(arguments, format);
	go_through(format, arguments, &i);
	va_end(arguments);
	return (i);
}
