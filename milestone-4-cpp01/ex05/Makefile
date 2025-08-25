# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/25 14:10:04 by elagouch          #+#    #+#              #
#    Updated: 2025/08/25 14:10:05 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# "Unnecessary violence"
NAME		= harl
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3
SRC			= main.cpp Harl.cpp
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

