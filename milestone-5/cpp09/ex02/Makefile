NAME		= PmergeMe
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -MMD -MP
CXXFLAGS	+= -Wconversion -pedantic -g3
SRC			= main.cpp PmergeMe.cpp
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

re: fclean
	$(MAKE) all

run10: $(NAME)
	@./$(NAME) "$$(shuf -i 1-10 -n 10|tr '\n' ' ')"

run10k: $(NAME)
	@./$(NAME) "$$(shuf -i 1-10000 -n 10000|tr '\n' ' ')"

-include $(SRC:.cpp=.d)

.PHONY: all clean fclean re

