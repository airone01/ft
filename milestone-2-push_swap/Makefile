# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:28:38 by elagouch          #+#    #+#              #
#    Updated: 2025/01/17 14:57:04 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk) # GPM!
# GPM: make_ansi_color_codes
COLOR			= $(COLOR_PUSH_SWAP)

# GPM: make_ansi_color_variables

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #
GPM_MSTONE	= 2
GPM_NAME	= push_swap
GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)
NAME		= push_swap
BNAME		= checker
DIR_OBJ 	= .obj/

# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #
ECHO	= printf
CC		= cc
AR		= ar
RM     	= rm -f
MD		= mkdir -p

# **************************************************************************** #
#                                    LIBFT                                     #
# **************************************************************************** #
LIBFT_DIR	= $(realpath ../milestone-0-libft)# GPM!
# GPM@ .LIBFT_DIR	= $(realpath ./libft)
GNL_DIR		= $(realpath ../milestone-1-get_next_line)# GPM!
LIBFT		= $(LIBFT_DIR)/libft.a
GNL			= $(GNL_DIR)/get_next_line.a # GPM!

# **************************************************************************** #
#                                    FLAGS                                     #
# **************************************************************************** #
CFLAGS			+= -Wall -Werror -Wextra -Wpedantic -MD -MP
CFLAGS			+= -I$(LIBFT_DIR) -I$(GNL_DIR) # GPM!
# GPM@ .CFLAGS			+= -I$(LIBFT_DIR)
LIBFT_FLAGS		+= -L$(LIBFT_DIR) -lft
GNL_FLAGS		+= -L$(GNL_DIR) -l:get_next_line.a # GPM!

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #
_SRC_GNL	=	get_next_line get_next_line_utils
# GPM: make_src_libft
# GPM: make_src_push_swap
include $(realpath ../extra-make/meta.mk) # GPM!
# GPM@ ._SRC_PUSH_SWAP_BONUS	+= $(_SRC_GNL)

# **************************************************************************** #
#                                   MAPPING                                    #
# **************************************************************************** #
SRC_LIBFT	= $(_SRC_LIBFT:%=$(LIBFT_DIR)/%.c)
SRC_GNL		= $(_SRC_GNL:%=$(GNL_DIR)/%.c) # GPM!
SRC			= $(_SRC_PUSH_SWAP:%=%.c)
SRC_BONUS	= $(_SRC_PUSH_SWAP_BONUS:%=%.c)
OBJ			= $(_SRC_PUSH_SWAP:%=$(DIR_OBJ)%.o)
DEP			= $(_SRC_PUSH_SWAP:%=$(DIR_OBJ)%.d)
OBJ_BONUS	= $(_SRC_PUSH_SWAP_BONUS:%=$(DIR_OBJ)%.o)
DEP_BONUS	= $(_SRC_PUSH_SWAP_BONUS:%=$(DIR_OBJ)%.d)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #
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
	@$(ECHO) "$(MSG) \n"
	@touch .title

$(LIBFT): $(SRC_LIBFT)
	@$(ECHO) "$(MSG) 🏗️  Building libft\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(GNL): $(SRC_GNL) # GPM!
	@$(ECHO) "$(MSG) 🏗️  Building GNL\n" # GPM!
	@$(MAKE) -C $(GNL_DIR) # GPM!
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
	@$(MAKE) -C $(GNL_DIR) clean # GPM!
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(ECHO) "$(MSG) 🧹 Fcleaning the project\n"
	@$(RM) $(NAME) $(BNAME)
	@$(MAKE) -C $(GNL_DIR) fclean # GPM!
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# **************************************************************************** #
#                                MAKE METADATA                                 #
# **************************************************************************** #
-include $(DEP) $(DEP_BONUS)
MAKEFLAGS	+= --no-print-directory
.PHONY: all bonus clean fclean re visualize visualizer # GPM!
# GPM@ ..PHONY: all bonus clean fclean re title
.SILENT: all bonus .bonus clean fclean re visualize visualizer # GPM!
# GPM@ ..SILENT: all bonus .bonus clean fclean re