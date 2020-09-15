# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouchau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 16:42:52 by abouchau          #+#    #+#              #
#    Updated: 2020/09/15 10:18:13 by abouchau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
LIBFT = libft
OS	= $(shell uname)
DIR_S = srcs
INCLUDES = -I includes/ -I libft/ -I $(MLX_DIR) -I get_next_line/
CC = clang
CFLAGS	= -O3 -Wall -Wextra -Werror
LIBS	= -L libft/ -lft ${MLX_LNK} -lm
GNLBUFF = -D BUFFER_SIZE=100
SOURCES =  srcs/move_cam.c \
	   srcs/parse_map.c \
	   srcs/ray_casting.c \
	   srcs/hooks.c \
	   srcs/draw.c \
	   srcs/draw_line.c \
	   srcs/check_and_parse.c \
	   get_next_line/get_next_line.c \
	   main.c

OBJS	= ${SOURCES:.c=.o}

ifeq ($(OS), Linux)
	MLX_DIR	= minilibx-linux/
	MLX_LNK	= -L ${MLX_DIR} -lmlx -lXext -lX11 -lbsd
else
	MLX_DIR	= minilibx-opengl
	MLX_LNK	= -L ${MLX_DIR} -lmlx -framework OpenGL -framework AppKit
endif

.c.o:
	${CC} ${CFLAGS} ${GNLBUFF} -c $< -o ${<:.c=.o} ${INC}

all : $(NAME)

${NAME}: ${OBJS} ft mlx
		${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${LIBS} -o ${NAME}

mlx:
	@make -C $(MLX_DIR)

ft:
	@make -C libft

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/*.h
	@mkdir -p objs
	@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<
clean :
	@rm -f $(OBJS)
	@make clean -C $(LIBFT)
	@make clean -C $(MLX_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make clean -C $(MLX_DIR)

re: fclean all

.PHONY:	clean fclean all re mlx ft
