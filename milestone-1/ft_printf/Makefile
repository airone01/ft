# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/16 14:11:35 by elagouch          #+#    #+#              #
#    Updated: 2026/03/16 14:14:20 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= ft_printf
CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra -Wpedantic -g3
ARFLAGS := -Wall -Werror -Wextra -Wpedantic -g3
SRC		:= ft_printf ft_putchar ft_putnbr_base_ssize ft_putstr_ssize
OBJ = $(SRC:.c=.o)

all: tags $(NAME)
tags:
	ctags *.c
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f tags
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all fclean re
	:Wall
