# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:28:38 by elagouch          #+#    #+#              #
#    Updated: 2025/01/27 22:42:39 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk) # GPM!
# GPM: make_ansi_color_codes
COLOR			= $(COLOR_PUSH_SWAP)

# **************************************************************************** #
#                            COMMON ANSI VARIABLES                             #
# **************************************************************************** #

# GPM: make_ansi_color_variables

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	= 2
GPM_NAME	= push_swap
GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)
NAME		= push_swap
BNAME		= checker
OUT_DIR 	= .out/

# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #

include $(realpath ../extra-make/commands.mk)
# GPM: make_commands

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

include $(realpath ../extra-make/flags.mk) # GPM!
# GPM: make_flags
CFLAGS			+= -I$(LIBFT_DIR) -I$(GNL_DIR) # GPM!
# GPM@ .CFLAGS			+= -I$(LIBFT_DIR)

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

# GPM: make_src
include $(realpath ../extra-make/sources.mk) # GPM!

# **************************************************************************** #
#                                   MAPPING                                    #
# **************************************************************************** #

SRC_LIBFT	= $(_SRC_LIBFT:%=$(LIBFT_DIR)/%.c)
SRC_GNL		= $(_SRC_GNL:%=$(GNL_DIR)/%.c) # GPM!
SRC			= $(_SRC_PUSH_SWAP:%=%.c)
SRC_BONUS	= $(_SRC_PUSH_SWAP_BONUS:%=%.c)
OBJ			= $(_SRC_PUSH_SWAP:%=$(OUT_DIR)%.o)
DEP			= $(_SRC_PUSH_SWAP:%=$(OUT_DIR)%.d)
OBJ_BONUS	= $(_SRC_PUSH_SWAP_BONUS:%=$(OUT_DIR)%.o)
DEP_BONUS	= $(_SRC_PUSH_SWAP_BONUS:%=$(OUT_DIR)%.d)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

include $(realpath ../extra-make/targets_common.mk) # GPM!
# GPM: make_target_common

title:
	@$(ECHO) "$(MSG)                  __\n"
	@$(ECHO) "$(MSG)   ___  __ _____ / /     ____    _____ ____\n"
	@$(ECHO) "$(MSG)  / _ \\/ // (_-</ _ \\   (_-< |/|/ / _ \`/ _ \\ \n"
	@$(ECHO) "$(MSG) / .__/\_,_/___/_//_/__/___/__,__/\\_,_/ .__/\n"
	@$(ECHO) "$(MSG)/_/                /___/             /_/\n"
	@$(ECHO) "$(MSG) \n"

include $(realpath ../extra-make/targets_bin_libft_gnl_bonus.mk) # GPM!
# GPM: make_target_bin_libft_bonus
# GPM!
visualizer: # GPM!
	cmake -B ../extra-ps-visualizer/build/ ../extra-ps-visualizer/ # GPM!
	make -C ../extra-ps-visualizer/build/ # GPM!
# GPM!
visualize: visualizer $(NAME) # GPM!
	../extra-ps-visualizer/build/bin/visualizer $(NAME) # GPM!

# **************************************************************************** #
#                                MAKE METADATA                                 #
# **************************************************************************** #

include $(realpath ../extra-make/make_meta.mk) # GPM!
# GPM: make_make_meta
