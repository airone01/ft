# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/09 13:22:22 by elagouch          #+#    #+#              #
#    Updated: 2025/05/11 12:46:45 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk)# GPM!
# GPM: make_art_mk
COLOR			= $(COLOR_PHILO)

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	:= 2
GPM_NAME	:= philo
GPM_MNAME	:= PHILO
NAME		:= philo
BNAME		:=
SRC_DIR		:= src/
OUT_DIR 	:= .out/

CFLAGS			:= -Iincludes

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: $(NAME)

title:
	@$(ECHO) "$(MSG)         __   _ __                   __ \n"
	@$(ECHO) "$(MSG)   ___  / /  (_) /__  ___ ___  ___  / /  ___ _______ \n"
	@$(ECHO) "$(MSG)  / _ \\/ _ \\/ / / _ \\(_-</ _ \\/ _ \\/ _ \\/ -_) __(_-< \n"
	@$(ECHO) "$(MSG) / .__/_//_/_/_/\\___/___/\\___/ .__/_//_/\\__/_/ /___/ \n"
	@$(ECHO) "$(MSG)/_/                         /_/ \n"
	@$(ECHO) "$(MSG)\n"

# GPM: make_sources_mk

# GPM: make_commands_mk

include $(realpath ../extra-make/targets_common.mk)# GPM!
# GPM: make_targets_common_mk

include $(realpath ../extra-make/targets_bin.mk)# GPM!
# GPM: make_targets_bin_mk