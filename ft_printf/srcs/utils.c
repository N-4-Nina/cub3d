/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:21:00 by abouchau          #+#    #+#             */
/*   Updated: 2019/12/16 13:33:59 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"
#include "../libft/libft.h"

int		isconvchar(char c)
{
	if (c == 'c' || c == 's' || c == 'p'
			|| c == 'd' || c == 'i' || c == 'u'
			|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

char	get_filler(t_flags argflags)
{
	if ((argflags.conversion == 'i' || argflags.conversion == 'd')
			&& argflags.zeropad == 1 && !argflags.minus
			&& (argflags.precision == 0))
		return ('0');
	if ((argflags.conversion == 'x' || argflags.conversion == 'X')
			&& argflags.zeropad == 1
			&& !argflags.minus && argflags.isprec == 0)
		return ('0');
	if (argflags.conversion == 'u' && !argflags.minus &&
			!argflags.isprec && argflags.zeropad == 1)
		return ('0');
	if (argflags.conversion == '%' && argflags.zeropad == 1 && !argflags.minus)
		return ('0');
	else
		return (' ');
}

void	fill_width(t_flags argflags, int sub, int *count)
{
	char	filler;
	int		width;

	if (!argflags.minwidth || (argflags.minwidth - sub) <= 0)
		return ;
	filler = get_filler(argflags);
	width = argflags.minwidth - sub + 1;
	while (--width && width > 0)
	{
		write(1, &filler, 1);
		(*count)++;
	}
}

void	handle_prec(int prec, int *count)
{
	int		i;

	i = 0;
	if (prec <= 0)
		return ;
	while (i < prec)
	{
		write(1, "0", 1);
		(*count) = (*count) + 1;
		i++;
	}
}
