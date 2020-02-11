/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:49:11 by abouchau          #+#    #+#             */
/*   Updated: 2019/12/16 12:50:19 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"
#include "../libft/libft.h"

void	ft_printstr_fd(char *s, int fd, t_flags argflags, int *count)
{
	int i;

	i = 0;
	if (argflags.isprec == 1)
		while (s[i] && i < argflags.precision)
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	else
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	(*count) += i;
}

void	write_c(t_flags argflags, va_list arguments, int *count)
{
	char	c;

	c = va_arg(arguments, int);
	if (!argflags.minus)
		fill_width(argflags, 1, count);
	write(1, &c, 1);
	*count = *count + 1;
	if (argflags.minus)
		fill_width(argflags, 1, count);
}

void	write_s(t_flags argflags, va_list arguments, int *count)
{
	char	*s;
	int		i;
	int		n;
	int		sub;

	i = 0;
	n = 0;
	if (!(s = va_arg(arguments, char*)))
	{
		s = ft_strdup("(null)");
		n = 1;
	}
	sub = calculate_string_subvalue(argflags, s);
	if (!argflags.minus)
		fill_width(argflags, sub, count);
	ft_printstr_fd(s, 1, argflags, count);
	if (argflags.minus)
		fill_width(argflags, sub, count);
	if (n == 1)
		free(s);
}
