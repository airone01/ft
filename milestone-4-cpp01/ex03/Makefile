# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/21 17:18:37 by elagouch          #+#    #+#              #
#    Updated: 2025/09/12 16:55:44 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# "Unnecessary violence"
NAME		= uv
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -MMD -MP
SRC			= main.cpp Weapon.cpp HumanA.cpp HumanB.cpp
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

