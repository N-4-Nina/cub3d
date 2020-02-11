/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nega_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:41:07 by abouchau          #+#    #+#             */
/*   Updated: 2019/12/16 13:27:22 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libftprintf.h"
#include "../libft/libft.h"

void	fill_f(t_flags argflags, int size, int *index)
{
	char	towrite;

	towrite = (argflags.conversion == 88) ? 'F' : 'f';
	while (size < 8)
	{
		write(1, &towrite, 1);
		size++;
		(*index)++;
	}
}

void	rec_printnegahexa(long n, t_flags argflags,
		char *array, int *index)
{
	char	*base;

	base = (argflags.conversion == 120) ? ft_strdup("fedcba9876543210") :
		ft_strdup("FEDCBA9876543210");
	if (n >= 0 && n < 16)
	{
		array[*index] = base[n];
		(*index)++;
	}
	else
	{
		rec_printnegahexa(n / 16, argflags, array, index);
		rec_printnegahexa(n % 16, argflags, array, index);
	}
	free(base);
}

int		find_index(char c, char *base)
{
	int i;

	i = 0;
	while (c != base[i])
		i++;
	return (i);
}

void	ft_addone(t_flags argflags, int size, int index, char *array)
{
	char *base;

	base = (argflags.conversion == 120) ? ft_strdup("fedcba9876543210") :
		ft_strdup("FEDCBA9876543210");
	if (index < 8 - size)
		return ;
	if (array[index] != 'f' && array[index] != 'F')
		array[index] = base[find_index(array[index], base) - 1];
	else
	{
		array[index] = '0';
		ft_addone(argflags, size, index - 1, array);
	}
}

void	ft_printnegahexa(long n, t_flags argflags, int *count, int *index)
{
	int		size;
	int		i;
	char	array[9];

	if (n == -2147483648)
	{
		write(1, "80000000", 8);
		(*count) += 8;
		return ;
	}
	array[8] = '\0';
	i = 0;
	size = get_hex_size(argflags, n);
	fill_f(argflags, size, index);
	rec_printnegahexa(n, argflags, array, index);
	ft_addone(argflags, size, 7, array);
	(*count) += 8;
	i = (*index) - size;
	while (array[i])
	{
		ft_putchar_fd(array[i], 1);
		i++;
	}
}
