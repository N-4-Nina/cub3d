/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_subvalue.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 10:10:00 by abouchau          #+#    #+#             */
/*   Updated: 2019/12/20 11:10:37 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"
#include "../libft/libft.h"

int	calculate_string_subvalue(t_flags argflags, char *s)
{
	int		sub;
	int		prec;
	int		size;
	int		isprec;

	prec = argflags.precision;
	size = (int)ft_strlen(s);
	isprec = argflags.isprec;
	if (isprec == 1 && prec > size && prec < argflags.minwidth)
		sub = size;
	else if (isprec == 1 && prec < size)
		sub = prec;
	else if (isprec == 1 && (prec < argflags.minwidth))
		sub = prec;
	else
		sub = size;
	return (sub);
}

int	calculate_int_subvalue(t_flags argflags, int i)
{
	int		sub;
	int		prec;
	int		isprec;
	int		size;

	prec = argflags.precision;
	isprec = argflags.isprec;
	size = get_int_size(argflags, i);
	if (isprec == 1 && prec > size && prec < argflags.minwidth && i >= 0)
		sub = prec;
	else if (argflags.isprec && i < 0 && size <= prec)
		sub = prec + 1;
	else if (isprec == 1 && prec < size)
		sub = size;
	else if (isprec == 1 && prec > argflags.minwidth)
		sub = prec;
	else if (isprec == 1 && prec == argflags.minwidth)
		sub = prec;
	else
		sub = size;
	return (sub);
}

int	calculate_unsigned_subvalue(t_flags argflags, unsigned int u)
{
	int	size;
	int	prec;
	int	isprec;

	prec = argflags.precision;
	isprec = argflags.isprec;
	size = get_unsize(argflags, u);
	if (isprec == 1 && prec > size && prec < argflags.minwidth)
		return (prec);
	else if (isprec == 1 && prec < size)
		return (size);
	else if (isprec == 1 && prec > argflags.minwidth)
		return (prec);
	else if (isprec == 1 && prec == argflags.minwidth)
		return (prec);
	else
		return (size);
}

int	calculate_hex_subvalue(t_flags argflags, int x)
{
	int	prec;
	int	size;

	size = (x < 0) ? 8 : get_hex_size(argflags, x);
	prec = argflags.precision;
	if (argflags.isprec && prec < argflags.minwidth && prec < size)
		return (size);
	else if (argflags.isprec && prec < argflags.minwidth)
		return (prec);
	else if (argflags.isprec && prec < size)
		return (prec + size);
	else if (argflags.isprec && prec > argflags.minwidth)
		return (prec);
	else if (argflags.isprec == 1 && prec == argflags.minwidth)
		return (prec);
	else
		return (size);
}
