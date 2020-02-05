/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p_and_percent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:50:39 by abouchau          #+#    #+#             */
/*   Updated: 2019/12/20 11:25:24 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

void	write_p(t_flags argflags, va_list arguments, int *count)
{
	int						i;
	int						sub;
	unsigned	long		p;

	i = 0;
	p = va_arg(arguments, unsigned long);
	sub = get_hex_size(argflags, p) + 2;
	(*count) = (*count) + 2;
	if (!argflags.minus)
		fill_width(argflags, sub, count);
	write(1, "0x", 2);
	ft_printhexa(p, 1, argflags, count);
	if (argflags.minus)
		fill_width(argflags, sub, count);
}

void	write_percent(t_flags argflags, int *count)
{
	if (!argflags.minus)
		fill_width(argflags, 1, count);
	write(1, "%", 1);
	(*count)++;
	if (argflags.minus)
		fill_width(argflags, 1, count);
}
