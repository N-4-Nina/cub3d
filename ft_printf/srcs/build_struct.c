/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:25:49 by abouchau          #+#    #+#             */
/*   Updated: 2019/12/16 14:08:33 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"

t_flags	*init_struct(void)
{
	t_flags *structure;

	if (!(structure = (t_flags*)malloc(sizeof(t_flags))))
		return (NULL);
	structure->minus = 0;
	structure->asterprec = 0;
	structure->zeropad = 0;
	structure->asterwidth = 0;
	structure->precision = 0;
	structure->isprec = 0;
	structure->minwidth = 0;
	structure->conversion = '\0';
	return (structure);
}

void	set_aster_width(t_flags *argflags,
		va_list arguments, int *iswidth)
{
	argflags->asterwidth = 1;
	argflags->minwidth = va_arg(arguments, int);
	if (argflags->minwidth < 0)
	{
		argflags->minwidth *= -1;
		argflags->minus = 1;
	}
	*iswidth = 1;
}

void	set_min_width(t_flags *argflags, int *iswidth,
			const char *value)
{
	argflags->minwidth = ft_atoi(value);
	*iswidth = 1;
}

void	set_precision(va_list arguments,
		t_flags *argflags, const char *next, int *iswidth)
{
	argflags->isprec = 1;
	if (ft_isdigit(next[0]))
		argflags->precision = ft_atoi(next);
	else if (next[0] == '*')
	{
		argflags->precision = va_arg(arguments, int);
		argflags->asterprec = 1;
	}
	else
		argflags->precision = 0;
	if (argflags->precision < 0)
	{
		argflags->precision = 0;
		argflags->isprec = 0;
	}
	(*iswidth) = 2;
}

t_flags	handle_arg(va_list arguments, const char *format)
{
	int		iswidth;
	int		i;
	t_flags	*argflags;

	iswidth = 0;
	i = 0;
	argflags = init_struct();
	while (!(isconvchar(format[i])))
	{
		if (format[i] == '-')
			argflags->minus = 1;
		if (format[i] == '0' && iswidth == 0)
			argflags->zeropad = 1;
		if (format[i] > 48 && format[i] < 58 && iswidth == 0)
			set_min_width(argflags, &iswidth, &format[i]);
		if (format[i] == '*' && format[i - 1] != '.')
			set_aster_width(argflags, arguments, &iswidth);
		if (format[i] == '.')
			set_precision(arguments, argflags, &format[i + 1], &iswidth);
		if (!(format[i + 1]))
			break ;
		i++;
	}
	argflags->conversion = format[i];
	return (*argflags);
}
