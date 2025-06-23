# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/22 17:54:18 by elagouch          #+#    #+#              #
#    Updated: 2025/06/23 15:02:07 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk)# GPM!
# GPM: make_art_mk
COLOR			= $(COLOR_CUB3D)

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	:= 2
GPM_NAME	:= cub3d
GPM_MNAME	:= CUB3D
NAME		:= cub3d
BNAME		:= cub3d_bonus
INC_DIR		:= includes/
SRC_DIR 	:= src/
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

all: $(NAME)

title:
	@$(ECHO) "$(MSG)           __   ____    __\n"
	@$(ECHO) "$(MSG) ______ __/ /  |_  /___/ /\n"
	@$(ECHO) "$(MSG)/ __/ // / _ \\_/_ </ _  /\n"
	@$(ECHO) "$(MSG)\__/\\_,_/_.__/____/\\_,_/\n"

include $(realpath ../extra-make/lib_libft.mk)# GPM!
# GPM: make_lib_libft_mk
include $(realpath ../extra-make/lib_ft_printf.mk)# GPM!
# GPM: make_lib_ft_printf_mk
include $(realpath ../extra-make/lib_get_next_line.mk)# GPM!
# GPM: make_lib_get_next_line_mk
include $(realpath ../extra-make/lib_minilibx.mk)# GPM!
# GPM: make_lib_minilibx_mk

# GPM: make_sources_mk

# GPM: make_commands_mk

include $(realpath ../extra-make/targets_common.mk)# GPM!
# GPM: make_targets_common_mk

include $(realpath ../extra-make/targets_bin.mk)# GPM!
# GPM: make_targets_bin_mk