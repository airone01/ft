# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/26 16:35:49 by elagouch          #+#    #+#              #
#    Updated: 2025/09/12 16:54:00 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fixed
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -MMP -MP
SRC			= main.cpp Fixed.cpp
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

