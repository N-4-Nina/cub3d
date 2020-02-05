# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouchau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/19 11:44:07 by abouchau          #+#    #+#              #
#    Updated: 2019/12/16 14:12:55 by abouchau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT = libft
DIR_S = srcs
DIR_O = objs
HEADER = includes
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SOURCES =   srcs/ft_printf.c \
	    			srcs/build_struct.c \
	    			srcs/calculate_subvalue.c \
	    			srcs/ft_printf.c \
	    			srcs/handle_char.c \
	    			srcs/handle_hex.c \
	    			srcs/handle_int.c \
	    			srcs/handle_nega_hex.c \
	    			srcs/handle_p_and_percent.c \
	    			srcs/handle_u.c \
				srcs/utils.c \

SRC_LFT =   libft/ft_atoi.c \
            libft/ft_isdigit.c \
            libft/ft_isprint.c \
						libft/ft_strdup.c \
            libft/ft_putnbr_fd.c \
	    			libft/ft_putchar_fd.c \
            libft/ft_putstr_fd.c \
            libft/ft_strlen.c \
            libft/ft_putchar_fd.c \
            libft/ft_putnbr_fd.c \
            libft/ft_putstr_fd.c
OBJS = $(SOURCES:.c=.o)
OBJS_LFT = $(SRC_LFT:.c=.o)
all : $(NAME)
$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@ar rc $(NAME) $(OBJS_LFT) $(OBJS)
	@ranlib $(NAME)
$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/ft_printf.h
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
