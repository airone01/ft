# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:28:38 by elagouch          #+#    #+#              #
#    Updated: 2025/02/04 13:26:57 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk) # GPM!
# GPM: make_ansi_color_codes
COLOR			= $(COLOR_FDF)

# **************************************************************************** #
#                            COMMON ANSI VARIABLES                             #
# **************************************************************************** #

# GPM: make_ansi_color_variables

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	= 2
GPM_NAME	= fdf
GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)
NAME		= fdf
BNAME		= bfdf
OUT_DIR 	= .out/

# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #

include $(realpath ../extra-make/commands.mk)
# GPM: make_commands

# **************************************************************************** #
#                                    LIBS                                      #
# **************************************************************************** #

LIBFT_DIR	= $(realpath ../milestone-0-libft)# GPM!
PRINTF_DIR	= $(realpath ../milestone-1-ft_printf)# GPM!
GNL_DIR		= $(realpath ../milestone-1-get_next_line)# GPM!

LIBFT		= $(LIBFT_DIR)/libft.a			# GPM!
PRINTF		= $(PRINTF_DIR)/libftprintf.a	# GPM!
GNL			= $(GNL_DIR)/libget_next_line.a	# GPM!

# **************************************************************************** #
#                                    FLAGS                                     #
# **************************************************************************** #

include $(realpath ../extra-make/flags.mk) # GPM!
# GPM: make_flags

CFLAGS			+= -I$(GNL_DIR) -I$(PRINTF_DIR) -I$(PRINTF_DIR) # GPM!

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

SRC			= $(_SRC_FDF_MANDATORY:%=%.c)
SRC_BONUS	= $(_SRC_FDF_BONUS:%=%.c)
OBJ			= $(_SRC_FDF_MANDATORY:%=$(OUT_DIR)%.o)
DEP			= $(_SRC_FDF_MANDATORY:%=$(OUT_DIR)%.d)
OBJ_BONUS	= $(_SRC_FDF_BONUS:%=$(OUT_DIR)%.o)
DEP_BONUS	= $(_SRC_FDF_BONUS:%=$(OUT_DIR)%.d)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

include $(realpath ../extra-make/targets_common.mk) # GPM!
# GPM: make_target_common

title:
	@$(ECHO) "$(MSG)   ___   _____\n"
	@$(ECHO) "$(MSG)  / _/__/ / _/\n"
	@$(ECHO) "$(MSG) / _/ _  / _/\n"
	@$(ECHO) "$(MSG)/_/ \\_,_/_/\n"
	@$(ECHO) "$(MSG)\n"

include $(realpath ../extra-make/targets_bin_libft_gnl_printf_bonus.mk) # GPM!
# GPM: make_target_bin_libft_gnl_printf_bonus

# **************************************************************************** #
#                                MAKE METADATA                                 #
# **************************************************************************** #

include $(realpath ../extra-make/make_meta.mk) # GPM!
# GPM: make_make_meta
