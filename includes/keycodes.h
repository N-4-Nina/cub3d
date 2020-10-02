/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpl <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 19:23:01 by chpl              #+#    #+#             */
/*   Updated: 2020/10/01 19:32:02 by chpl             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# ifdef __linux__
#  define LTURN 65361
#  define RTURN 65363

#  define FORWARD 122
#  define LEFT 113
#  define RIGHT 100
#  define BACK 115
#  define ESCAPE 65307

# else
#  define LTURN 123
#  define RTURN 124
#  define FORWARD 13
#  define LEFT 0
#  define RIGHT 2
#  define BACK 1
#  define ESCAPE 53

# endif
#endif
