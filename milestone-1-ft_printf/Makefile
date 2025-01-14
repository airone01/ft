# ------------- ANSI -------------
TITLE		= \033[48;5;202;30;1m
RESET		= \033[0m
GREEN		= \033[1;32m
MSG			= $(TITLE) $(GPM_FNAME) \t$(RESET)
SUCCESS		= $(MSG) $(GREEN)✅ Successfully built! 🚀$(RESET)

# ------------- Meta -------------
GPM_MSTONE	= 1
GPM_NAME	= ft_printf
GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)
NAME		= libftprintf.a
DIR_OBJ 	= .obj/

# ----------- Commands -----------
ECHO		= printf
CC			= cc
AR			= ar
RM      	= rm -f
MD			= mkdir -p

# ------------- Flags ------------
CFLAGS		= -Wall -Werror -Wextra -Wpedantic -MMD -MP
ARFLAGS		= rcs

# ------------ Sources -----------
SRC			=				\
	ft_printf.c				\
	ft_putchar.c			\
	ft_putnbr_base_ssize.c	\
	ft_putstr_ssize.c		\
	ft_strlen.c

# ------------ Mapping -----------
OBJ			= $(SRC:%.c=$(DIR_OBJ)%.o)
DEP			= $(SRC:%.c=$(DIR_OBJ)%.d)

# ------------ Targets -----------
all: $(NAME)

$(NAME): $(OBJ)
	@$(ECHO) "$(MSG) ⏳ Building $(NAME)\n"
	@$(AR) $(ARFLAGS) $(NAME) $?
	@$(ECHO) "$(SUCCESS)\n"

$(DIR_OBJ)%.o: %.c Makefile
	@$(MD) $(DIR_OBJ)
	@$(ECHO) "$(MSG) ⏳ $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(ECHO) "$(MSG) 🧹 Cleaning the project\n"
	@$(RM) -r $(DIR_OBJ)

fclean: clean
	@$(ECHO) "$(MSG) 🧹 Fcleaning the project\n"
	@$(RM) $(NAME)

re: fclean all

# ----------- Make meta ----------
MAKEFLAGS	+= --no-print-directory
-include $(DEP)
.PHONY: all clean fclean re
.SILENT: clean fclean
