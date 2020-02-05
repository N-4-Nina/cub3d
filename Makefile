# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouchau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 16:42:52 by abouchau          #+#    #+#              #
#    Updated: 2020/02/05 17:01:54 by abouchau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
LIBFT = ft_printf/libft
DIR_S = srcs
DIR_O = objs
HEADER = includes
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SOURCES =   srcs/*.c

OBJS = $(SOURCES:.c=.o)

all : $(NAME)
$(NAME): $(OBJS)
	@$(CC) -I /usr/X11/include -g -D BUFFER_SIZE=100 -framework OpenGL -framework Appkit $(OBJS)
$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/*.h
	@mkdir -p objs
	@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<
clean :
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)
fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
re: fclean all

.PHONY:	clean fclean all re
