# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    art.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:45:02 by elagouch          #+#    #+#              #
#    Updated: 2025/01/16 17:06:08 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GPM? begin make_ansi_color_codes
# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

COLOR_LIBFT			= 78
COLOR_FT_PRINTF		= 202
COLOR_GET_NEXT_LINE	= 198
COLOR_PUSH_SWAP		= 227
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
PADDING_LENGTH	= $(shell echo $$(($(DESIRED_WIDTH) - $(shell echo "$(GPM_NAME) " | wc -c))))
PADDING			= $(shell printf '%*s' $(PADDING_LENGTH))
# Define message with dynamic padding
MSG				= $(TITLE) $(GPM_FNAME) $(RESET)$(PADDING)
SUCCESS			= $(MSG) $(GREEN)✅ Successfully built! 🚀$(RESET)
SUCCESSB		= $(MSG) $(GREEN)✅ Successfully built bonuses! 🚀$(RESET)
# GPM? end make_ansi_color_variables

#   ___ __   _____
#  / (_) /  / _/ /_
# / / / _ \/ _/ __/
#/_/_/_.__/_/ \__/

#   _____               _      __  ___
#  / _/ /_    ___  ____(_)__  / /_/ _/
# / _/ __/   / _ \/ __/ / _ \/ __/ _/
#/_/ \__/___/ .__/_/ /_/_//_/\__/_/
#      /___/_/

#            __                  __     ___
#  ___ ____ / /_   ___  _____ __/ /_   / (_)__  ___
# / _ `/ -_) __/  / _ \/ -_) \ / __/  / / / _ \/ -_)
# \_, /\__/\__/__/_//_/\__/_\_\\__/__/_/_/_//_/\__/
#/___/       /___/               /___/

#                  __
#   ___  __ _____ / /     ____    _____ ____
#  / _ \/ // (_-</ _ \   (_-< |/|/ / _ `/ _ \
# / .__/\_,_/___/_//_/__/___/__,__/\_,_/ .__/
#/_/                /___/             /_/
