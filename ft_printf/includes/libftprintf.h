/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:27:14 by abouchau          #+#    #+#             */
/*   Updated: 2019/12/16 14:00:06 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct		s_flags
{
	int		minus;
	int		zeropad;
	int		minwidth;
	int		asterprec;
	int		asterwidth;
	int		precision;
	int		isprec;
	char	conversion;
}					t_flags;

int					isconvchar(char c);
t_flags				*init_struct(void);
t_flags				handle_arg(va_list arguments, const char *format);
int					dispatch(t_flags argflags, va_list arguments, int *count);
int					go_through(const char *format,
					va_list arguments, int *count);
int					ft_printf(const char *format, ...);

void				set_aster_width(t_flags *argflags, va_list arguments,
				int *iswidth);
void				set_min_width(t_flags *argflags,
				int *iswidth, const char *value);
t_flags				handle_arg(va_list arguments, const char *format);

void				write_c(t_flags argflags, va_list arguments, int *count);
void				write_s(t_flags argflags, va_list arguments, int *count);
void				write_i(t_flags argflags, va_list arguments, int *count);
void				write_p(t_flags argflags, va_list arguments, int *count);
void				write_u(t_flags argflags, va_list arguments, int *count);
void				write_x(t_flags argflags, va_list arguments, int *count);
void				write_percent(t_flags argflags, int *count);

char				get_filler(t_flags argflags);
void				fill_width(t_flags argflags, int sub, int *count);
void				fill_f(t_flags argflags, int size, int *index);
void				handle_prec(int prec, int *count);
int					get_int_size(t_flags argflags, long n);
int					get_unsize(t_flags argflags, unsigned int n);
int					get_hex_size(t_flags argflags,
					long n);
void				handle_negative(int i, int fd,
				t_flags argflags, int *count);
void				ft_printnbr_fd(long n, int fd, int prec, int *count);
void				ft_printunsigned_fd(unsigned int n,
				int fd, int prec, int *count);
void				ft_printstr_fd(char *s, int fd,
				t_flags argflags, int *count);
void				ft_printhexa(long n, int fd, t_flags argflags, int *count);
void				ft_printnegahexa(long n, t_flags argflags,
				int *count, int *index);

int					calculate_string_subvalue(t_flags argflags, char *s);
int					calculate_int_subvalue(t_flags argflags, int i);
int					calculate_hex_subvalue(t_flags argflags, int x);
int					calculate_unsigned_subvalue(t_flags argflags,
					unsigned int u);
#endif
