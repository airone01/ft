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

# ------------ Libft ------------# GPM!
LIBFT_DIR	= $(realpath ../milestone-0-libft)# GPM!
# GPM!
# ------------- Flags ------------
CFLAGS		= -Wall -Werror -Wextra -Wpedantic -MMD -MP
ARFLAGS		= rcs

# ------------ Sources -----------
_SRC		=				\
	ft_printf				\
	ft_putchar				\
	ft_putnbr_base_ssize	\
	ft_putstr_ssize
# GPM@ ._SRC		+=	ft_strlen

# ------------ Mapping -----------
OBJ			= $(_SRC:%=$(DIR_OBJ)%.o)
DEP			= $(_SRC:%=$(DIR_OBJ)%.d)

# ------------ Targets -----------
all: .title $(NAME)

.title:
	@$(ECHO) "$(MSG)   ___  __                                       __       ___ \n"
	@$(ECHO) "$(MSG) /'___\\/\\ \\__                         __        /\\ \\__  /'___\\ \n"
	@$(ECHO) "$(MSG)/\\ \\__/\\ \\ ,_\\          _____   _ __ /\\_\\    ___\\ \\ ,_\\/\\ \\__/ \n"
	@$(ECHO) "$(MSG)\\ \\ ,__\\\\\\\\ \\ \\/         /\\ '__\`\\/\\\`'__\\/\\ \\ /' _ \`\\ \\ \\/\\ \\ ,__\\ \n"
	@$(ECHO) "$(MSG) \\ \\ \\_/ \\ \\ \\_        \\ \\ \\L\\ \\ \\ \\/ \\ \\ \\/\\ \\/\\ \\ \\ \\_\\ \\ \\_/ \n"
	@$(ECHO) "$(MSG)  \\ \\_\\   \\ \\__\\        \\ \\ ,__/\\ \\_\\  \\ \\_\\ \\_\\ \\_\\ \\__\\\\\\\\ \\_\\ \n"
	@$(ECHO) "$(MSG)   \\/_/    \\/__/  _______\\ \\ \\/  \\/_/   \\/_/\\/_/\\/_/\\/__/ \\/_/ \n"
	@$(ECHO) "$(MSG)                 /\\______\\\\\\\\ \\_\\ \n"
	@$(ECHO) "$(MSG)                 \\/______/ \\/_/ \n"
	@$(ECHO) "$(MSG)\n"
	@touch .title

# GPM@ .$(NAME): $(OBJ)
$(NAME): $(OBJ) $(LIBFT_DIR)/.obj/ft_strlen.o # GPM!
	@$(ECHO) "$(MSG) 🏗️  Building $(NAME)\n"
	@$(AR) $(ARFLAGS) $(NAME) $? # GPM!
# GPM@ .	@$(AR) $(ARFLAGS) $(NAME) $?
	@$(ECHO) "$(SUCCESS)\n"

$(LIBFT_DIR)/.obj/ft_strlen.o: $(LIBFT_DIR)/ft_strlen.c $(LIBFT_DIR)/Makefile # GPM!
	@$(MD) $(LIBFT_DIR)/.obj/ # GPM!
	@$(CC) $(CFLAGS) -c $< -o $@ # GPM!
# GPM!
$(DIR_OBJ)%.o: %.c Makefile
	@$(MD) $(DIR_OBJ)
	@$(ECHO) "$(MSG) ⏳ $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(ECHO) "$(MSG) 🧹 Cleaning the project\n"
	@$(RM) -r $(DIR_OBJ) .title

fclean: clean
	@$(ECHO) "$(MSG) 🧹 Fcleaning the project\n"
	@$(RM) $(NAME)

re: fclean all

# ----------- Make meta ----------
MAKEFLAGS	+= --no-print-directory
-include $(DEP)
.PHONY: all clean fclean re title
