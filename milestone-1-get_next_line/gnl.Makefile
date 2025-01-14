# **************************************************************************** #
#                                                                              #
#                                                       _    ⣀⣀⣀⡀⡀⡀⡀⣀⡀⣀⣀⣀⡀  #
#    Makefile                                       _ _/ |   ⡇⣶⡆⡇⡾⢏⡭⡵⠀⡇⣶⡆⡇  #
#                                                  | '_| |_  ⣓⣒⠒⡃⡂⣏⡆⡯⢇⠓⠶⠖⡃  #
#    By: elagouch <elagouch@student.42.fr>         |_|_|_(@) ⢻⣊⡞⣪⢳⡗⣳⢤⣈⢍⣰⢖⡇  #
#                                                  | | |_  ) ⠜⡲⡢⣲⡯⡼⡑⡁⣝⣘⡚⢠⠅  #
#    Created: 2024/11/05 15:39:47 by elagouch      |_  _/ /  ⡖⣒⡒⡆⠉⠧⢰⣮⣇⣂⡏⡳⡆  #
#    Updated: 2024/11/18 11:13:41 by elagouch        |_/___| ⣇⣛⣃⡇⡿⢤⠤⠾⠡⠹⢝⣚⡁  #
#                                                                              #
# **************************************************************************** #

# ------------- Meta -------------
MAKEFLAGS	+= --no-print-directory
.PHONY: all clean fclean re

# ------------- ANSI -------------
TITLE	    = \033[48;5;198;30;1m
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
RM     	= rm -f
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
SRC	=							\
	get_next_line.c				\
	get_next_line_utils.c
#	get_next_line_bonus.c		\
#	get_next_line_utils_bonus.c
SRC_TEST =	\
	main.c

# ------------ Mapping -----------
OBJ	= $(SRC:%.c=$(DIR_OBJ)%.o)
DEP	= $(SRC:%.c=$(DIR_OBJ)%.d)
OBJ_BONUS	= $(SRC_BONUS:%.c=$(DIR_OBJ)%.o)
DEP_BONUS	= $(SRC_BONUS:%.c=$(DIR_OBJ)%.d)
OBJ_TEST	= $(SRC_TEST:%.c=$(DIR_OBJ)%.o)
DEP_TEST	= $(SRC_TEST:%.c=$(DIR_OBJ)%.d)

# ------------ Targets -----------
all: $(NAME)

$(LIBFT):
	@$(ECHO) "$(MSG) ⏳ Building libft\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(ECHO) "$(MSG) ⏳ Building $(NAME)\n"
	@$(AR) $(ARFLAGS) $(NAME) $?
	@$(ECHO) "$(SUCCESS)\n"

$(DIR_OBJ)%.o: %.c get_next_line.h gnl.Makefile
	@$(MD) $(DIR_OBJ)
	@$(ECHO) "$(MSG) ⏳ $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

checker: $(OBJ) $(OBJ_TEST) | $(LIBFT)
	@$(ECHO) "$(MSG) ⏳ Building $(NAME)\n"
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
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# ----------- Make meta ----------
-include $(DEP) $(DEP_BONUS) $(DEP_TEST)
