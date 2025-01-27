# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    commands.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:17:31 by elagouch          #+#    #+#              #
#    Updated: 2025/01/23 13:36:14 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #

# GPM? begin make_commands
ECHO		= printf
MAKE		= make
CC			= cc
AR			= ar rcs
CARGO_BUILD	= RUSTFLAGS="-Awarnings"; cargo build --release
RM			= rm -rf
MD			= mkdir -p
# GPM? end make_commands
