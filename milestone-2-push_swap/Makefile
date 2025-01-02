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

# ------------- ANSI -------------
TITLE_SEC	= \033[48;5;78;30;1m
RESET		= \033[0m

# ------------- Meta -------------
GPM_MSTONE	= 2
GPM_NAME	= push_swap
GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)
NAME		= push_swap
DIR_OBJ 	= .obj/

# ----------- Commands -----------
ECHO	= echo
MAKE	= make
CC		= cc
AR		= ar
RM     	= rm -f
MD		= mkdir -p

# ------------ Libft ------------
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

# ------------- Flags ------------
CFLAGS			= -Wall -Werror -Wextra -Wpedantic -MMD -MP -g3
CFLAGS			+= -I$(LIBFT_DIR)
ARFLAGS			= rcs
LIBFT_FLAGS		= -L$(LIBFT_DIR) -lft

# ------------ Sources -----------
SRC	=						\
	ft_abs.c				\
	mani_swap.c				\
	mani_push.c				\
	mani_rotate.c			\
	mani_rrotate.c			\
	parse_stdin.c			\
	push_swap.c				\
	sort_cheapest.c			\
	sort_cost.c				\
	sort_large.c			\
	sort_move.c				\
	sort_push_save_three.c	\
	sort_shift_back.c		\
	sort_tiny.c				\
	stack_add_back.c		\
	stack_clear.c			\
	stack_del_one.c			\
	stack_indexes.c			\
	stack_iter.c			\
	stack_last.c			\
	stack_lowest_pos.c		\
	stack_max.c				\
	stack_new.c				\
	stack_pos.c				\
	stack_size.c			\
	stack_sorted.c			\
	std_error.c

# ------------ Mapping -----------
OBJ	= $(SRC:%.c=$(DIR_OBJ)%.o)
DEP	= $(SRC:%.c=$(DIR_OBJ)%.d)

# ------------ Targets -----------
all: $(NAME)

$(LIBFT):
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Building libft"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Building $(NAME)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_FLAGS)

$(DIR_OBJ)%.o: %.c Makefile
	@$(MD) $(DIR_OBJ)
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)... $@"
	@$(CC) $(CFLAGS) -c $< -o $@

visualizer:
	cmake -B ./push_swap_visualizer/build/ ./push_swap_visualizer/
	make -C ./push_swap_visualizer/build/

visualize: visualizer $(NAME)
	./push_swap_visualizer/build/bin/visualizer $(NAME)

clean:
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Cleaning the project"
	@$(RM) -r $(DIR_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Fcleaning the project"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# ----------- Make meta ----------
MAKEFLAGS	+= --no-print-directory
-include $(DEP)
.PHONY: all clean fclean re
.SILENT: clean fclean