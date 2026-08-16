NAME = B
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): y.tab.c lex.yy.c
	$(CC) $(CFLAGS) -o $(NAME) y.tab.c lex.yy.c

y.tab.c y.tab.h: parser.y
	yacc -d parser.y

lex.yy.c: lexer.l y.tab.h
	lex lexer.l

clean:
	rm -f lex.yy.c y.tab.c y.tab.h

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
