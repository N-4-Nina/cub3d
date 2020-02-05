/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:30:56 by abouchau          #+#    #+#             */
/*   Updated: 2019/12/23 11:23:22 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"
#include "../libft/libft.h"
#include <limits.h>

int main(void)
{
	char 		*string = "variable";
	int		i = 812;
	void		*ptr;
	char	c = '\0';
	int returnvalue;
	int OGreturnvalue;
	int	a;
	unsigned	int	u = 179861862;
	ptr = &c;

	returnvalue = ft_printf("ft%X, %4.3d, %4.3d, %4.3d, %4.3d, %4.3d", INT_MIN, -12, 123456789, 0, -123456789, 97);
	OGreturnvalue = printf("pft%X, %4.3d, %4.3d, %4.3d, %4.3d, %4.3d", INT_MIN, -12, 123456789, 0, -123456789, 97);
	//write(1, "\n", 1);
	ft_printf("the value returned by ftprintf() is : -- %i --\n", returnvalue);
	printf("the value returned by printf() is : -- %i --\n", OGreturnvalue);

	//	printf("og = %x \n", 140);
	//	ft_printf("ft = %x \n", 140);
	//ft_printf("ft=%s\n", 42);
}
