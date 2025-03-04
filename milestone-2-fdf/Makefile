# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:28:38 by elagouch          #+#    #+#              #
#    Updated: 2025/03/04 15:28:56 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk)# GPM!
# GPM: make_art_mk
COLOR			= $(COLOR_FDF)

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	:= 2
GPM_NAME	:= fdf
GPM_MNAME	:= FDF
NAME		:= fdf
BNAME		:= bfdf
SRC_DIR		:= src/
OUT_DIR 	:= .out/

# **************************************************************************** #
#                                    LIBS                                      #
# **************************************************************************** #

LIBFT_DIR		:= $(realpath ../milestone-0-libft)# GPM!
PRINTF_DIR		:= $(realpath ../milestone-1-ft_printf)# GPM!
GNL_DIR			:= $(realpath ../milestone-1-get_next_line)# GPM!
MINILIBX_DIR	:= $(realpath ../extra-minilibx)# GPM!
# GPM@	.LIBFT_DIR		:= $(realpath ./libft)
# GPM@	.PRINTF_DIR		:= $(realpath ./ft_printf)
# GPM@	.GNL_DIR		:= $(realpath ./get_next_line)
# GPM@	.MINILIBX_DIR	:= $(realpath ./minilibx)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

# Needed because we compile with the math library
LDFLAGS			:= -lm
CFLAGS			:= -I.

all: $(NAME)

title:
	@$(ECHO) "$(MSG)   ___   _____\n"
	@$(ECHO) "$(MSG)  / _/__/ / _/\n"
	@$(ECHO) "$(MSG) / _/ _  / _/\n"
	@$(ECHO) "$(MSG)/_/ \\_,_/_/\n"
	@$(ECHO) "$(MSG)\n"

include $(realpath ../extra-make/lib_libft.mk)# GPM!
# GPM: make_lib_libft_mk
include $(realpath ../extra-make/lib_get_next_line.mk)# GPM!
# GPM: make_lib_get_next_line_mk
include $(realpath ../extra-make/lib_ft_printf.mk)# GPM!
# GPM: make_lib_ft_printf_mk
include $(realpath ../extra-make/lib_minilibx.mk)
# GPM: make_lib_minilibx_mk

# GPM: make_sources_mk

# GPM: make_commands_mk

include $(realpath ../extra-make/targets_common.mk)# GPM!
# GPM: make_targets_common.mk

include $(realpath ../extra-make/targets_bin.mk)
# GPM: make_targets_bin_mk
