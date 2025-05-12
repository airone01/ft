# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:28:38 by elagouch          #+#    #+#              #
#    Updated: 2025/05/12 02:08:46 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk)# GPM!
# GPM: make_art_mk
COLOR			= $(COLOR_PIPEX)

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	:= 2
GPM_NAME	:= pipex
GPM_MNAME	:= PIPEX
NAME		:= pipex
BNAME		:= pipex
OUT_DIR 	:= .out/

# **************************************************************************** #
#                                    LIBS                                      #
# **************************************************************************** #

LIBFT_DIR	= $(realpath ../milestone-0-libft)# GPM!
PRINTF_DIR	= $(realpath ../milestone-1-ft_printf)# GPM!
GNL_DIR		= $(realpath ../milestone-1-get_next_line)# GPM!
# GPM@	.LIBFT_DIR	:= $(realpath ./libft)
# GPM@	.PRINTF_DIR	:= $(realpath ./ft_printf)
# GPM@	.GNL_DIR	:= $(realpath ./get_next_line)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: $(NAME)

title:
	@$(ECHO) "$(MSG)         _\n"
	@$(ECHO) "$(MSG)   ___  (_)__  _____ __\n"
	@$(ECHO) "$(MSG)  / _ \\/ / _ \\/ -_) \\ /\n"
	@$(ECHO) "$(MSG) / .__/_/ .__/\\__/_\\_\\ \n"
	@$(ECHO) "$(MSG)/_/    /_/\n"

include $(realpath ../extra-make/lib_libft.mk)# GPM!
# GPM: make_lib_libft_mk
include $(realpath ../extra-make/lib_ft_printf.mk)# GPM!
# GPM: make_lib_ft_printf_mk
include $(realpath ../extra-make/lib_get_next_line.mk)# GPM!
# GPM: make_lib_get_next_line_mk

# GPM: make_sources_mk

# GPM: make_commands_mk

include $(realpath ../extra-make/targets_common.mk)# GPM!
# GPM: make_targets_common_mk

include $(realpath ../extra-make/targets_bin.mk)# GPM!
# GPM: make_targets_bin_mk
