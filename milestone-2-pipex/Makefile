# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:28:38 by elagouch          #+#    #+#              #
#    Updated: 2025/02/10 19:47:37 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk) # GPM!
COLOR			= $(COLOR_PIPEX)

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	= 2
GPM_NAME	= pipex
GPM_MNAME	= PIPEX
NAME		= pipex
BNAME		= bpipex
OUT_DIR 	= .out/

# **************************************************************************** #
#                                    LIBS                                      #
# **************************************************************************** #

LIBFT_DIR	= $(realpath ../milestone-0-libft)# GPM!
PRINTF_DIR	= $(realpath ../milestone-1-ft_printf)# GPM!
GNL_DIR		= $(realpath ../milestone-1-get_next_line)# GPM!

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: title $(NAME)

title:
	@$(ECHO) "$(MSG)         _\n"
	@$(ECHO) "$(MSG)   ___  (_)__  _____ __\n"
	@$(ECHO) "$(MSG)  / _ \\/ / _ \\/ -_) \\ /\n"
	@$(ECHO) "$(MSG) / .__/_/ .__/\\__/_\\_\\ \n"
	@$(ECHO) "$(MSG)/_/    /_/\n"
	@$(ECHO) "$(MSG)\n"

include $(realpath ../extra-make/lib_ft_printf.mk)
include $(realpath ../extra-make/lib_get_next_line.mk)
include $(realpath ../extra-make/lib_libft.mk)

include $(realpath ../extra-make/targets_common.mk) # GPM!
# GPM: make_target_common

include $(realpath ../extra-make/targets_bin.mk)

