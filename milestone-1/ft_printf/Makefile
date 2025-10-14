# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 19:35:51 by elagouch          #+#    #+#              #
#    Updated: 2025/05/12 02:08:31 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk)# GPM!
# GPM: make_art_mk
COLOR			= $(COLOR_FT_PRINTF)

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	:= 1
GPM_NAME	:= ft_printf
GPM_MNAME	:= FT_PRINTF
NAME		:= libftprintf.a
BNAME		:= blibftprintf.a
SRC_DIR 	:= src/
OUT_DIR 	:= .out/

# **************************************************************************** #
#                                    LIBS                                      #
# **************************************************************************** #

LIBFT_DIR		:= $(realpath ../milestone-0-libft)# GPM!
# GPM@	.LIBFT_DIR	= $(realpath ../libft)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: $(NAME)

title:
	@$(ECHO) "$(MSG)   _____               _      __  ___\n"
	@$(ECHO) "$(MSG)  / _/ /_    ___  ____(_)__  / /_/ _/\n"
	@$(ECHO) "$(MSG) / _/ __/   / _ \/ __/ / _ \\/ __/ _/\n"
	@$(ECHO) "$(MSG)/_/ \__/___/ .__/_/ /_/_//_/\\__/_/\n"
	@$(ECHO) "$(MSG)      /___/_/\n"

include $(realpath ../extra-make/lib_libft.mk)# GPM!
# GPM: make_lib_libft_mk

# GPM: make_sources_mk

# GPM: make_commands_mk

include $(realpath ../extra-make/targets_common.mk)# GPM!
# GPM: make_targets_common_mk

include $(realpath ../extra-make/targets_lib.mk)# GPM!
# GPM: make_targets_lib_mk
