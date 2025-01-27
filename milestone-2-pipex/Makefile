# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:28:38 by elagouch          #+#    #+#              #
#    Updated: 2025/01/23 16:20:03 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk) # GPM!
# GPM: make_ansi_color_codes
COLOR			= $(COLOR_PIPEX)

# **************************************************************************** #
#                            COMMON ANSI VARIABLES                             #
# **************************************************************************** #

# GPM: make_ansi_color_variables

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	= 2
GPM_NAME	= pipex
GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)
NAME		= pipex
BNAME		= bpipex
OUT_DIR 	= .out/

# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #

include $(realpath ../extra-make/commands.mk)
# GPM: make_commands

# **************************************************************************** #
#                                    LIBS                                      #
# **************************************************************************** #

LIBFT_DIR	= $(realpath ../milestone-0-libft) # GPM!
_			= $(shell echo $(LIBFT_DIR)) # GPM!
GNL_DIR		= $(realpath ../milestone-1-get_next_line) # GPM!
PRINTF_DIR	= $(realpath ../milestone-1-ft_printf) # GPM!

LIBFT		= $(LIBFT_DIR)/libft.a # GPM!
GNL			= $(GNL_DIR)/get_next_line.a # GPM!
PRINTF		= $(PRINTF_DIR)/libftprintf.a # GPM!

# **************************************************************************** #
#                                    FLAGS                                     #
# **************************************************************************** #

include $(realpath ../extra-make/flags.mk) # GPM!
# GPM: make_flags

CFLAGS			+= -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR) # GPM!

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

# GPM: make_src
include $(realpath ../extra-make/sources.mk) # GPM!

# **************************************************************************** #
#                                   MAPPING                                    #
# **************************************************************************** #

# GPM: make_src_pipex

SRC_LIBFT	= $(_SRC_LIBFT:%=$(LIBFT_DIR)/%.c)		# GPM!
SRC_GNL		= $(_SRC_GNL:%=$(GNL_DIR)/%.c)			# GPM!
SRC_PRINTF	= $(_SRC_PRINTF:%=$(PRINTF_DIR)/%.c)	# GPM!

SRC			= $(_SRC_PIPEX:%=%.c)
SRC_BONUS	= $(_SRC_PIPEX_BONUS:%=%.c)
OBJ			= $(_SRC_PIPEX:%=$(OUT_DIR)%.o)
DEP			= $(_SRC_PIPEX:%=$(OUT_DIR)%.d)
OBJ_BONUS	= $(_SRC_PIPEX_BONUS:%=$(OUT_DIR)%.o)
DEP_BONUS	= $(_SRC_PIPEX_BONUS:%=$(OUT_DIR)%.d)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

include $(realpath ../extra-make/targets_common.mk) # GPM!
# GPM: make_target_common

.title:
	@$(ECHO) "$(MSG)         _\n"
	@$(ECHO) "$(MSG)   ___  (_)__  _____ __\n"
	@$(ECHO) "$(MSG)  / _ \\/ / _ \\/ -_) \\ /\n"
	@$(ECHO) "$(MSG) / .__/_/ .__/\\__/_\\_\\ \n"
	@$(ECHO) "$(MSG)/_/    /_/\n"
	@$(ECHO) "$(MSG) \n"
	@touch .title

include $(realpath ../extra-make/targets_bin_libft_gnl_printf_bonus.mk) # GPM!
# GPM: make_target_bin_libft_gnl_printf_bonus

# **************************************************************************** #
#                                MAKE METADATA                                 #
# **************************************************************************** #

include $(realpath ../extra-make/make_meta.mk) # GPM!
# GPM: make_make_meta
