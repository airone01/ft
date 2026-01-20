NAME		= mutated
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -MMD -MP
CXXFLAGS	+= -Wconversion -pedantic -g3
SRC			= main.cpp
SRC_HTPL	= MutantStack.hpp
OBJ			= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(SRC:.cpp=.d) $(SRC_HTPL:.hpp=.d) $(SRC_HTPL:.hpp=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean
	make all

-include $(SRC:.cpp=.d)

.PHONY: all clean fclean re

