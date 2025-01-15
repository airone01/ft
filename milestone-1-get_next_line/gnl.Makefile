# ------------- Meta -------------
MAKEFLAGS	+= --no-print-directory
.PHONY: all clean fclean re

# ------------- ANSI -------------
TITLE		= \033[48;5;198;30;1m
RESET		= \033[0m
GREEN		= \033[1;32m
MSG			= $(TITLE) $(GPM_FNAME) \t\t$(RESET)
SUCCESS		= $(MSG) $(GREEN)✅ Successfully built! 🚀$(RESET)
SUCCESSB	= $(MSG) $(GREEN)✅ Successfully built bonuses! 🚀$(RESET)

# ------------- Meta -------------
GPM_MSTONE	= 1
GPM_NAME	= get_next_line
GPM_FNAME	= $(GPM_MSTONE)-gnl
NAME		= get_next_line.a
DIR_OBJ 	= .obj/

# ----------- Commands -----------
ECHO	= printf
MAKE	= make
CC		= cc
AR		= ar
RM		= rm -f
MD		= mkdir -p

# ------------ Libft ------------
LIBFT_DIR	= $(realpath ../milestone-0-libft)
LIBFT		= $(LIBFT_DIR)/libft.a

# ------------- Flags ------------
CFLAGS			+= -Wall -Werror -Wextra -MMD -MP -g3
CFLAGS			+= -I$(LIBFT_DIR) -I$(realpath .)
LIBFT_FLAGS		+= -L$(LIBFT_DIR) -lft
ARFLAGS			= rcs

# ------------ Sources -----------
_SRC	=					\
	get_next_line
# GPM@ _SRC += get_next_line_utils
_SRC_TEST =	\
	main

# ------------ Mapping -----------
OBJ			= $(_SRC:%=$(DIR_OBJ)%.o)
DEP			= $(_SRC:%=$(DIR_OBJ)%.d)
OBJ_BONUS	= $(_SRC_BONUS:%=$(DIR_OBJ)%.o)
DEP_BONUS	= $(_SRC_BONUS:%=$(DIR_OBJ)%.d)
OBJ_TEST	= $(_SRC_TEST:%=$(DIR_OBJ)%.o)
DEP_TEST	= $(_SRC_TEST:%=$(DIR_OBJ)%.d)

# ------------ Targets -----------
all: .title $(NAME)

.title:
	@$(ECHO) "$(MSG)               ___ \n"
	@$(ECHO) "$(MSG)              /\\_ \\ \n"
	@$(ECHO) "$(MSG)   __     ___ \\//\\ \\ \n"
	@$(ECHO) "$(MSG) /'_ \`\\ /' _ \`\\ \\ \\ \\ \n"
	@$(ECHO) "$(MSG)/\\ \\L\\ \\/\\ \\/\\ \\ \\_\\ \\_ \n"
	@$(ECHO) "$(MSG)\\ \\____ \\ \\_\\ \\_\\/\\____\\ \n"
	@$(ECHO) "$(MSG) \\/___L\\ \\/_/\\/_/\\/____/ \n"
	@$(ECHO) "$(MSG)   /\\____/ \n"
	@$(ECHO) "$(MSG)   \\_/__/ \n"
	@$(ECHO) "$(MSG)\n"
	@touch .title

$(LIBFT):
	@$(ECHO) "$(MSG) 🏗️  Building libft\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(ECHO) "$(MSG) 🏗️  Building $(NAME)\n"
	@$(AR) $(ARFLAGS) $(NAME) $?
	@$(ECHO) "$(SUCCESS)\n"

$(DIR_OBJ)%.o: %.c
	@$(MD) $(DIR_OBJ)
	@$(ECHO) "$(MSG) ⏳ $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

checker: $(OBJ) $(OBJ_TEST) $(LIBFT)
	@$(ECHO) "$(MSG) 🏗️  Building $(NAME)\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)

test: $(NAME)
	@$(ECHO) "$(MSG) 🧪 Testing $(NAME)\n"
	@$(MAKE) -C $(realpath ./tester) m

clean:
	@$(ECHO) "$(MSG) 🧹 Cleaning the project\n"
	@$(RM) -r $(DIR_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(ECHO) "$(MSG) 🧹 Fcleaning the project\n"
	@$(RM) $(NAME) .title
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# ----------- Make meta ----------
-include $(DEP) $(DEP_BONUS) $(DEP_TEST)
