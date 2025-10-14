# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/22 12:35:35 by elagouch          #+#    #+#              #
#    Updated: 2025/08/26 19:16:05 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk)# GPM!
# GPM: make_art_mk_ansi
COLOR			= 250;119;85

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	:= 4
GPM_NAME	:= cpp03
GPM_MNAME	:= CPP03

# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #

include $(realpath ../extra-make/commands.mk)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: ex00 ex01 ex02

ex00: title
	@$(ECHO) "$(MSG)🏗️  Building ex00: Aaaaand... OPEN!\n"
	@$(MAKE) -sC ex00

ex01: title
	@$(ECHO) "$(MSG)🏗️  Building ex01: Serena, my love!\n"
	@$(MAKE) -sC ex01

ex02: title
	@$(ECHO) "$(MSG)🏗️  Building ex02: Repetitive work\n"
	@$(MAKE) -sC ex02

title:
	@$(ECHO) "$(MSG)                ___  ____\n"
	@$(ECHO) "$(MSG) _______  ___  / _ \\|_  /\n"
	@$(ECHO) "$(MSG)/ __/ _ \\/ _ \\/ // //_ <\n"
	@$(ECHO) "$(MSG)\\__/ .__/ .__/\\___/____/\n"
	@$(ECHO) "$(MSG)  /_/  /_/\n"
	@$(ECHO) "$(MSG) \n"

clean:
	@$(ECHO) "$(MSG)🧹 Cleaning $(GPM_NAME)\n"
	@$(MAKE) -sC ex00 clean
	@$(MAKE) -sC ex01 clean
	@$(MAKE) -sC ex02 clean

fclean:
	@$(ECHO) "$(MSG)🧹 Fcleaning $(GPM_NAME)\n"
	@$(MAKE) -sC ex00 fclean
	@$(MAKE) -sC ex01 fclean
	@$(MAKE) -sC ex02 fclean

re: fclean all

MAKEFLAGS	+= --no-print-directory
.PHONY: all clean fclean re title ex00 ex01 ex02
