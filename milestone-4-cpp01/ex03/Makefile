# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/21 17:18:37 by elagouch          #+#    #+#              #
#    Updated: 2025/08/21 18:05:13 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# "Unnecessary violence"
NAME		= uv
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3
SRC			= main.cpp Weapon.cpp HumanA.cpp HumanB.cpp
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

