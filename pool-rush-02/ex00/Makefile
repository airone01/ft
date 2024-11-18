# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@42>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/28 10:51:47 by elagouch          #+#    #+#              #
#    Updated: 2024/09/29 23:10:05 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG = rush-02
CC = cc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -g3
SRC = main.c					\
      ft_atoi.c					\
      ft_itoa.c					\
      ft_join.c					\
      ft_putstr.c				\
      ft_split.c				\
      ft_strcat.c				\
      ft_strcmp.c				\
	  ft_strcpy.c				\
      ft_strdup.c				\
	  ft_strlcat.c				\
      ft_strlen.c				\
	  ft_strncpy.c				\
      ft_strnew.c				\
	  rush_check_charset.c		\
      rush_count_words.c		\
      rush_find_word.c			\
      rush_putnbr_lang.c		\
      rush_putnbr_lang_qty.c	\
      rush_putnbr_lang_extra.c
OBJ = $(SRC:.c=.o)

all: $(PROG)
$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(PROG)
re: fclean all

.PHONY: all fclean re
