# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/22 12:00:00 by elagouch          #+#    #+#              #
#    Updated: 2025/08/20 12:55:18 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= brainz
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
SRC			= main.cpp Zombie.cpp newZombie.cpp randomChump.cpp
OBJ			= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

