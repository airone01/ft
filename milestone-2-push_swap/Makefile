# ------------- ANSI -------------
TITLE		= \033[48;5;227;30;1m
RESET		= \033[0m
GREEN		= \033[1;32m
MSG			= $(TITLE) $(GPM_FNAME) \t$(RESET)
SUCCESS		= $(MSG) $(GREEN)✅ Successfully built! 🚀$(RESET)
SUCCESSB	= $(MSG) $(GREEN)✅ Successfully built bonuses! 🚀$(RESET)

# ------------- Meta -------------
GPM_MSTONE	= 2
GPM_NAME	= push_swap
GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)
NAME		= push_swap
BNAME		= checker
DIR_OBJ 	= .obj/

# ----------- Commands -----------
ECHO	= printf
CC		= cc
AR		= ar
RM     	= rm -f
MD		= mkdir -p

# ------------ Libft ------------
LIBFT_DIR	= $(realpath ../milestone-0-libft)# GPM!
# GPM@ .LIBFT_DIR	= $(realpath ./libft)
GNL_DIR		= $(realpath ../milestone-1-get_next_line)# GPM!
LIBFT		= $(LIBFT_DIR)/libft.a
GNL			= $(GNL_DIR)/get_next_line.a # GPM!

# ------------- Flags ------------
CFLAGS			+= -Wall -Werror -Wextra -Wpedantic -MD -MP
CFLAGS			+= -I$(LIBFT_DIR) -I$(GNL_DIR) # GPM!
# GPM@ .CFLAGS			+= -I$(LIBFT_DIR) # GPM!
LIBFT_FLAGS		+= -L$(LIBFT_DIR) -lft
GNL_FLAGS		+= -L$(GNL_DIR) -l:get_next_line.a # GPM!

# ------------ Sources -----------
_SRC_GNL	=	get_next_line get_next_line_utils # GNL!
_SRC_LIBFT	=				\
	ft_atoi					\
	ft_abs					\
	ft_bzero				\
	ft_calloc				\
	ft_isalnum				\
	ft_isalpha				\
	ft_isascii				\
	ft_isdigit				\
	ft_isprint				\
	ft_itoa					\
	ft_memchr				\
	ft_memcmp				\
	ft_memcpy				\
	ft_memmove				\
	ft_memset				\
	ft_putchar_fd			\
	ft_putendl_fd			\
	ft_putnbr_fd			\
	ft_putstr_fd			\
	ft_split				\
	ft_strdup				\
	ft_strrchr				\
	ft_strchr				\
	ft_strcmp				\
	ft_striteri				\
	ft_strjoin				\
	ft_strlcat				\
	ft_strlcpy				\
	ft_strlen				\
	ft_strmapi				\
	ft_strnstr				\
	ft_strncmp				\
	ft_strtrim				\
	ft_tolower				\
	ft_toupper				\
	ft_substr
_SRC_COMMON	=				\
	args_legit				\
	mani_swap				\
	mani_push				\
	mani_rotate				\
	mani_rrotate			\
	parse_stdin				\
	sort_cheapest			\
	sort_cost				\
	sort_large				\
	sort_move				\
	sort_push_save_three	\
	sort_shift_back			\
	sort_tiny				\
	stack_add_back			\
	stack_clear				\
	stack_clear_error		\
	stack_dupes				\
	stack_indexes			\
	stack_iter				\
	stack_last				\
	stack_legit				\
	stack_lowest_pos		\
	stack_max				\
	stack_new				\
	stack_pos				\
	stack_size				\
	stack_sorted			\
	std_error
_SRC = $(_SRC_COMMON)		\
	push_swap
_SRC_BONUS = $(_SRC_COMMON)	\
	checker					\
	checker_utils
# GPM@ ._SRC_BONUS += get_next_line

# ------------ Mapping -----------
SRC_LIBFT	= $(_SRC_LIBFT:%=$(LIBFT_DIR)/%.c)
SRC_GNL		= $(_SRC_GNL:%=$(GNL_DIR)/%.c) # GNL!
SRC			= $(_SRC:%=%.c)
SRC_BONUS	= $(_SRC_BONUS:%=%.c)
OBJ			= $(_SRC:%=$(DIR_OBJ)%.o)
DEP			= $(_SRC:%=$(DIR_OBJ)%.d)
OBJ_BONUS	= $(_SRC_BONUS:%=$(DIR_OBJ)%.o)
DEP_BONUS	= $(_SRC_BONUS:%=$(DIR_OBJ)%.d)

# ------------ Targets -----------
all: .title $(NAME)

.title:
	@$(ECHO) "$(MSG)                        __ \n"
	@$(ECHO) "$(MSG)                       /\\ \\ \n"
	@$(ECHO) "$(MSG) _____   __  __    ____\\ \\ \\___              ____  __  __  __     __     _____ \n"
	@$(ECHO) "$(MSG)/\\ '__\`\\/\\ \\/\\ \\  /',__\\\\\\\\ \\  _ \`\\           /',__\\/\\ \\/\\ \\/\\ \\  /'__\`\\  /\\ '__\`\\ \n"
	@$(ECHO) "$(MSG)\\ \\ \\L\\ \\ \\ \\_\\ \\/\\__, \`\\\\\\\\ \\ \\ \\ \\         /\\__, \`\\ \\ \\_/ \\_/ \\/\\ \\L\\.\\_\\ \\ \\L\\ \\ \n"
	@$(ECHO) "$(MSG) \\ \\ ,__/\\ \\____/\\/\\____/ \\ \\_\\ \\_\\        \\/\\____/\\ \\___x___/'\\ \\__/.\\_\\\\\\\\ \\ ,__/ \n"
	@$(ECHO) "$(MSG)  \\ \\ \\/  \\/___/  \\/___/   \\/_/\\/_/  _______\\/___/  \\/__//__/   \\/__/\\/_/ \\ \\ \\/ \n"
	@$(ECHO) "$(MSG)   \\ \\_\\                            /\\______\\                              \\ \\_\\ \n"
	@$(ECHO) "$(MSG)    \\/_/                            \\/______/                               \\/_/ \n"
	@$(ECHO) "$(MSG)\n"
	@touch .title

$(LIBFT): $(SRC_LIBFT)
	@$(ECHO) "$(MSG) 🏗️  Building libft\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(GNL): $(SRC_GNL) # GPM!
	@$(ECHO) "$(MSG) 🏗️  Building GNL\n" # GPM!
	@$(MAKE) -C $(GNL_DIR) -f gnl.Makefile # GPM!
# GPM!
$(NAME): $(OBJ) $(LIBFT)
	@$(ECHO) "$(MSG) 🏗️  Building $(NAME)\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)
	@$(ECHO) "$(SUCCESS)\n"

$(DIR_OBJ)%.o: %.c Makefile
	@$(MD) $(DIR_OBJ)
	@$(ECHO) "$(MSG) ⏳ $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

# GPM@ ..bonus: $(OBJ_BONUS) $(LIBFT)
.bonus: $(OBJ_BONUS) $(LIBFT) $(GNL) # GPM!
	@$(ECHO) "$(MSG) 🏗️  Building bonuses for $(NAME)\n"
	@$(CC) $(CFLAGS) -o $(BNAME) $^ $(GNL_FLAGS) $(LIBFT_FLAGS) # GPM!
	# GPM@ .	@$(CC) $(CFLAGS) -o  $(BNAME) $^ $(LIBFT_FLAGS)
	@touch .bonus
	@$(ECHO) "$(SUCCESSB)\n"

bonus: .bonus
 # GPM!
visualizer: # GPM!
	cmake -B ../extra-ps-visualizer/build/ ../extra-ps-visualizer/ # GPM!
	make -C ../extra-ps-visualizer/build/ # GPM!
 # GPM!
visualize: visualizer $(NAME) # GPM!
	../extra-ps-visualizer/build/bin/visualizer $(NAME) # GPM!

clean:
	@$(ECHO) "$(MSG) 🧹 Cleaning the project\n"
	@$(RM) -r $(DIR_OBJ) .title
	@$(MAKE) -C $(GNL_DIR) -f gnl.Makefile clean # GPM!

fclean: clean
	@$(ECHO) "$(MSG) 🧹 Fcleaning the project\n"
	@$(RM) $(NAME) $(BNAME)
	@$(MAKE) -C $(GNL_DIR) -f gnl.Makefile fclean # GPM!

re: fclean all

# ----------- Make meta ----------
-include $(DEP) $(DEP_BONUS)
MAKEFLAGS	+= --no-print-directory
.PHONY: all bonus clean fclean re visualize visualizer # GPM!
# GPM@ ..PHONY: all bonus clean fclean re title
.SILENT: all bonus .bonus clean fclean re visualize visualizer # GPM!
# GPM@ ..SILENT: all bonus .bonus clean fclean re
