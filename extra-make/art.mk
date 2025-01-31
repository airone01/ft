# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    art.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:45:02 by elagouch          #+#    #+#              #
#    Updated: 2025/01/31 15:41:10 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #
# GPM? begin make_ansi_color_codes
# Common core projects
COLOR_FT			= 99
COLOR_LIBFT			= 78
COLOR_B2BR			= 208
COLOR_FT_PRINTF		= 202
COLOR_GET_NEXT_LINE	= 198
COLOR_PUSH_SWAP		= 227
COLOR_PIPEX			= 160
# Extra projects
COLOR_MINECRAFT		= 34
COLOR_ARTHUR		= 33
# GPM? end make_ansi_color_codes
# GPM? begin make_ansi_color_variables
# **************************************************************************** #
#                            COMMON ANSI VARIABLES                             #
# **************************************************************************** #

TITLE			= \033[48;5;$(COLOR);30;1m
RESET			= \033[0m
GREEN			= \033[1;32m
# Calculate padding length (you can adjust the total desired width)
DESIRED_WIDTH	= 14
PADDING_LENGTH	= $(shell echo $$(($(DESIRED_WIDTH) - $(shell echo "$(GPM_FNAME) " | wc -c))))
PADDING			= $(shell printf '%*s' $(PADDING_LENGTH))
# Define message with dynamic padding
MSG				= $(TITLE) $(GPM_FNAME) $(PADDING)$(RESET) ${}
SUCCESS			= $(MSG)$(GREEN)✅ Successfully built! 🚀$(RESET)
SUCCESSB		= $(MSG)$(GREEN)✅ Successfully built bonuses! 🚀$(RESET)
# GPM? end make_ansi_color_variables
