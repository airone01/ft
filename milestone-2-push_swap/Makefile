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
ECHO	= echo -e
MAKE	= make
CC		= cc
AR		= ar
RM     	= rm -f
MD		= mkdir -p

# ------------ Libft ------------
LIBFT_DIR	= $(realpath ../milestone-0-libft)
GNL_DIR		= $(realpath ../milestone-1-get_next_line)
LIBFT		= $(LIBFT_DIR)/libft.a
GNL			= $(GNL_DIR)/get_next_line.a

# ------------- Flags ------------
CFLAGS			+= -Wall -Werror -Wextra -MMD -MP -g3
CFLAGS			+= -I$(LIBFT_DIR) -I$(GNL_DIR)
LIBFT_FLAGS		+= -L$(LIBFT_DIR) -lft
GNL_FLAGS		+= -L$(GNL_DIR) -l:get_next_line.a

# ------------ Sources -----------
SRC_COMMON	=				\
	args_legit.c			\
	ft_abs.c				\
	get_next_line.c			\
	mani_swap.c				\
	mani_push.c				\
	mani_rotate.c			\
	mani_rrotate.c			\
	parse_stdin.c			\
	sort_cheapest.c			\
	sort_cost.c				\
	sort_large.c			\
	sort_move.c				\
	sort_push_save_three.c	\
	sort_shift_back.c		\
	sort_tiny.c				\
	stack_add_back.c		\
	stack_clear.c			\
	stack_clear_error.c		\
	stack_dupes.c			\
	stack_indexes.c			\
	stack_iter.c			\
	stack_last.c			\
	stack_legit.c			\
	stack_lowest_pos.c		\
	stack_max.c				\
	stack_new.c				\
	stack_pos.c				\
	stack_size.c			\
	stack_sorted.c			\
	std_error.c
SRC = $(SRC_COMMON)	\
	push_swap.c
SRC_BONUS = $(SRC_COMMON)	\
	checker.c				\
	checker_utils.c

# ------------ Mapping -----------
OBJ	= $(SRC:%.c=$(DIR_OBJ)%.o)
DEP	= $(SRC:%.c=$(DIR_OBJ)%.d)
OBJ_BONUS	= $(SRC_BONUS:%.c=$(DIR_OBJ)%.o)
DEP_BONUS	= $(SRC_BONUS:%.c=$(DIR_OBJ)%.d)

# ------------ Targets -----------
all: $(NAME)

$(LIBFT):
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Building libft"
	@$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Building libft"
	@$(MAKE) -C $(GNL_DIR) -f gnl.Makefile

$(NAME): $(OBJ) | $(LIBFT)
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Building $(NAME)"
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)

$(DIR_OBJ)%.o: %.c Makefile
	@$(MD) $(DIR_OBJ)
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)... $@"
	@$(CC) $(CFLAGS) -c $< -o $@

.bonus: $(OBJ_BONUS) | $(LIBFT) $(GNL)
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Building bonuses for $(NAME)"
	$(CC) $(CFLAGS) -o checker $^ $(GNL_FLAGS) $(LIBFT_FLAGS)
	@touch .bonus

bonus: .bonus # Temp file to avoid unnecessary rebuilds

visualizer:
	cmake -B ../extra-ps-visualizer/build/ ../extra-ps-visualizer/
	make -C ../extra-ps-visualizer/build/

visualize: visualizer $(NAME)
	../extra-ps-visualizer/build/bin/visualizer $(NAME)

clean:
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Cleaning the project"
	@$(RM) -r $(DIR_OBJ)
	@$(MAKE) -C $(GNL_DIR) -f gnl.Makefile clean

fclean: clean
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Fcleaning the project"
	@$(RM) $(NAME)
	@$(MAKE) -C $(GNL_DIR) -f gnl.Makefile fclean

re: fclean all

# ----------- Make meta ----------
-include $(DEP) $(DEP_BONUS)
MAKEFLAGS	+= --no-print-directory
.PHONY: all clean fclean re