NAME = B
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME): y.tab.c lex.yy.c
	@echo " CC   $<"
	@$(CC) $(CFLAGS) -o $(NAME) y.tab.c lex.yy.c
	@ls -lah $(NAME)

y.tab.c y.tab.h: src/parser.y
	@echo " YACC $<"
	@yacc -d src/parser.y

lex.yy.c: src/lexer.l y.tab.h
	@echo " LEX  $<"
	@lex src/lexer.l

clean:
	@rm -fv lex.yy.c y.tab.c y.tab.h

fclean: clean
	@rm -fv $(NAME)

re: fclean all

.PHONY: all clean fclean re
