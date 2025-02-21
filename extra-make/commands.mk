# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    commands.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:17:31 by elagouch          #+#    #+#              #
#    Updated: 2025/02/21 11:18:38 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GPM? begin make_commands_mk
# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #

ECHO		= printf
MAKE		= make
CC			= cc
AR			= ar rcs
CARGO_BUILD	= RUSTFLAGS="-Awarnings"; cargo build --release
RM			= rm -rf
MD			= mkdir -p
TOUCH		= touch
# GPM? end make_commands_mk
