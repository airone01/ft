# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/22 12:00:00 by elagouch          #+#    #+#              #
#    Updated: 2025/06/22 13:33:06 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= phonebook
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3
SRC			= main.cpp PhoneBook.cpp Contact.cpp
OBJ			= $(SRC:.cpp=.o)
HEADERS		= Contact.hpp PhoneBook.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

