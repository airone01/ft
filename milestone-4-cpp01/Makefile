# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/22 12:35:35 by elagouch          #+#    #+#              #
#    Updated: 2025/08/25 14:32:23 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk)# GPM!
# GPM: make_art_mk
COLOR			= 250;119;85

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	:= 4
GPM_NAME	:= cpp00
GPM_MNAME	:= CPP00

# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #

include $(realpath ../extra-make/commands.mk)
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: ex00 ex01 ex02 ex03 ex04 ex05

ex00: title
	@$(ECHO) "$(MSG)🏗️  Building ex00: BraiiiiiiinnnzzzZ\n"
	@$(MAKE) -sC ex00

ex01: title
	@$(ECHO) "$(MSG)🏗️  Building ex01: Moar brainz!\n"
	@$(MAKE) -sC ex01

ex02: title
	@$(ECHO) "$(MSG)🏗️  Building ex02: HI THIS IS BRAIN\n"
	@$(MAKE) -sC ex02

ex03: title
	@$(ECHO) "$(MSG)🏗️  Building ex03: Unnecessary violence\n"
	@$(MAKE) -sC ex03

ex04: title
	@$(ECHO) "$(MSG)🏗️  Building ex04: Sed is for losers\n"
	@$(MAKE) -sC ex04

ex05: title
	@$(ECHO) "$(MSG)🏗️  Building ex05: Harl 2.0\n"
	@$(MAKE) -sC ex05

title:
	@$(ECHO) "$(MSG)                ___ ___\n"
	@$(ECHO) "$(MSG) _______  ___  / _ <  /\n"
	@$(ECHO) "$(MSG)/ __/ _ \\/ _ \\/ // / /\n"
	@$(ECHO) "$(MSG)\\__/ .__/ .__/\\___/_/\n"
	@$(ECHO) "$(MSG)  /_/  /_/\n"
	@$(ECHO) "$(MSG) \n"

clean:
	@$(ECHO) "$(MSG)🧹 Cleaning cpp00\n"
	@$(MAKE) -sC ex00 clean
	@$(MAKE) -sC ex01 clean
	@$(MAKE) -sC ex02 clean
	@$(MAKE) -sC ex03 clean

fclean:
	@$(ECHO) "$(MSG)🧹 Fcleaning cpp00\n"
	@$(MAKE) -sC ex00 fclean
	@$(MAKE) -sC ex01 fclean
	@$(MAKE) -sC ex02 fclean
	@$(MAKE) -sC ex03 fclean

re: fclean all

# GPM: make_sources_mk

# GPM: make_commands_mk

MAKEFLAGS	+= --no-print-directory
.PHONY: all clean fclean re title ex00 ex01 ex02
