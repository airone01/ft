# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 16:42:17 by elagouch          #+#    #+#              #
#    Updated: 2025/05/12 02:09:49 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk)# GPM!
# GPM: make_art_mk
COLOR			= $(COLOR_MINISHELL)

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	:= 2
GPM_NAME	:= minishell
GPM_MNAME	:= MINISHELL
NAME		:= minishell
BNAME		:=
SRC_DIR 	:= src/
OUT_DIR 	:= .out/

# **************************************************************************** #
#                                    LIBS                                      #
# **************************************************************************** #

LIBFT_DIR		:= $(realpath ../milestone-0-libft)# GPM!
PRINTF_DIR		:= $(realpath ../milestone-1-ft_printf)# GPM!
# GPM@	.LIBFT_DIR	= $(realpath ./libft)
# GPM@	.PRINTF_DIR	= $(realpath ./ft_printf)

LDFLAGS			:= -lreadline

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: $(NAME)

title:
	@$(ECHO) "$(MSG)         _      _     __       ____\n"
	@$(ECHO) "$(MSG)  __ _  (_)__  (_)__ / /  ___ / / /\n"
	@$(ECHO) "$(MSG) /  ' \\/ / _ \\/ (_-</ _ \\/ -_) / /\n"
	@$(ECHO) "$(MSG)/_/_/_/_/_//_/_/___/_//_/\\__/_/_/\n"

include $(realpath ../extra-make/lib_libft.mk)# GPM!
# GPM: make_lib_libft_mk
include $(realpath ../extra-make/lib_ft_printf.mk)# GPM!
# GPM: make_lib_ft_printf_mk

# GPM: make_sources_mk

# GPM: make_commands_mk

include $(realpath ../extra-make/targets_common.mk)# GPM!
# GPM: make_targets_common_mk

include $(realpath ../extra-make/targets_bin.mk)# GPM!
# GPM: make_targets_bin_mk
