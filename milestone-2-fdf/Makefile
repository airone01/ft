# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:28:38 by elagouch          #+#    #+#              #
#    Updated: 2025/02/05 01:03:48 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk) # GPM!
# GPM: make_ansi_color_codes
COLOR			= $(COLOR_FDF)

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	= 2
GPM_NAME	= fdf
GPM_MNAME	= FDF
GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)
NAME		= fdf
BNAME		= bfdf
OUT_DIR 	= .out/

# **************************************************************************** #
#                                    LIBS                                      #
# **************************************************************************** #

LIBFT_DIR		:= $(realpath ../milestone-0-libft)
PRINTF_DIR		:= $(realpath ../milestone-1-ft_printf)
GNL_DIR			:= $(realpath ../milestone-1-get_next_line)
MINILIBX_DIR	:= $(realpath ../extra-minilibx)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: title $(NAME)

title:
	@$(ECHO) "$(MSG)   ___   _____\n"
	@$(ECHO) "$(MSG)  / _/__/ / _/\n"
	@$(ECHO) "$(MSG) / _/ _  / _/\n"
	@$(ECHO) "$(MSG)/_/ \\_,_/_/\n"
	@$(ECHO) "$(MSG)\n"
	# @$(ECHO) "$(MSG)DEBUG:\n"
	# @$(ECHO) "$(MSG)Deps are $(NAME_DEPS_INDIRECT)\n"
	# @$(ECHO) "$(MSG)\n"

include $(realpath ../extra-make/lib_libft.mk)
include $(realpath ../extra-make/lib_ft_printf.mk)
include $(realpath ../extra-make/lib_get_next_line.mk)
include $(realpath ../extra-make/lib_minilibx.mk)

include $(realpath ../extra-make/targets_common.mk) # GPM!
# GPM: make_target_common
