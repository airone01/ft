# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@42>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 10:52:47 by elagouch          #+#    #+#              #
#    Updated: 2024/10/02 19:34:51 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq
CC = cc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -g3
SRC = main.c					\
	  ft_atoi.c					\
	  ft_file.c					\
	  ft_free_op.c				\
      ft_putstr.c				\
	  ft_str_is_alpha.c			\
      ft_strsplit.c				\
      ft_strcat.c				\
      ft_strcmp.c				\
	  ft_strcount_words.c		\
	  ft_strcpy.c				\
	  ft_strcut.c				\
      ft_strdup.c				\
      ft_strjoin.c				\
	  ft_strlcat.c				\
      ft_strlen.c				\
	  ft_strncpy.c				\
      ft_strnew.c				\
	  bsq_map_op.c				\
	  bsq_map_op2.c				\
      bsq_map_put.c				\
      bsq_map_read.c			\
      bsq_map_read2.c			\
      bsq_map_size.c			\
	  bsq_solve.c
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
