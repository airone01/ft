# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/22 12:00:00 by elagouch          #+#    #+#              #
#    Updated: 2025/09/12 16:56:06 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= more_brainz
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -MMD -MP
SRC			= main.cpp Zombie.cpp zombieHorde.cpp
OBJ			= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(SRC:.cpp=.d)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(SRC:.cpp=.d)

.PHONY: all clean fclean re

