# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@42>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/22 18:31:06 by elagouch          #+#    #+#              #
#    Updated: 2024/09/22 18:31:46 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG = rush-01
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = main.c \
      ft_math.c ft_str.c \
      solve_max.c solve_min.c \
      grid.c dupe.c \
      check.c brute.c 
OBJ = $(SRC:.c=.o)

build_all: $(PROG)
$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
clean_all: clean
	rm -f $(PROG)
again: clean_all build_all
test: again
	./$(PROG)

.PHONY: build_all clean_all again test
