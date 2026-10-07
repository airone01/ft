NAME = B
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

CYNHB := \e[1;105;30m
CRESET := \e[0m

all: $(NAME)

$(NAME): y.tab.c lex.yy.c
	@printf "$(CYNHB) CC  $(CRESET) $<\n"
	@$(CC) $(CFLAGS) -o $(NAME) y.tab.c lex.yy.c
	@printf "      $(NAME)\n"

y.tab.c y.tab.h: src/parser.y
	@printf "$(CYNHB) YCC $(CRESET) $<\n"
	@yacc -d src/parser.y

lex.yy.c: src/lexer.l y.tab.h
	@printf "$(CYNHB) LEX $(CRESET) $<\n"
	@lex src/lexer.l

clean:
	@rm -fv lex.yy.c y.tab.c y.tab.h

fclean: clean
	@rm -fv $(NAME)

bonus: all

re: fclean all

.PHONY: all bonus clean fclean re
