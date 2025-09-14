# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    art.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:45:02 by elagouch          #+#    #+#              #
#    Updated: 2025/06/22 18:06:19 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

# GPM? begin make_art_mk
# Common core projects
COLOR_FT			= 139;92;246
COLOR_LIBFT			= 153;95;227
COLOR_B2BR			= 167;96;209
COLOR_FT_PRINTF		= 181;95;190
COLOR_GET_NEXT_LINE	= 196;92;170
COLOR_PUSH_SWAP		= 209;87;150
COLOR_PIPEX			= 223;80;129
COLOR_FDF			= 237;70;107
COLOR_MINISHELL		= 245;77;93
COLOR_PHILO			= 248;99;89
COLOR_CPP00			= 250;119;85
COLOR_CUB3D			= 251;138;79

# result of ./gradient.sh -v 15 #8b5cf6 #f43f5e #facc15

# 139;92;246
# 153;95;227
# 167;96;209
# 181;95;190
# 196;92;170
# 209;87;150
# 223;80;129
# 237;70;107
# 245;77;93
# 248;99;89
# 250;119;85
# 251;138;79

# 252;155;71

# 252;172;61
# 251;188;47


# Extra projects
COLOR_MINECRAFT		= 252;172;61
COLOR_ARTHUR		= 251;188;47

# GPM? begin make_art_mk_ansi
# **************************************************************************** #
#                            COMMON ANSI VARIABLES                             #
# **************************************************************************** #

TITLE			= \033[48;2;$(COLOR);30;1m
RESET			= \033[0m
GREEN			= \033[1;32m

# Calculate padding length (you can adjust the total desired width)
DESIRED_WIDTH	= 17
PADDING_LENGTH	= $(shell echo $$(($(DESIRED_WIDTH) - $(shell echo "$(GPM_FNAME) " | wc -c))))
PADDING			= $(shell printf '%*s' $(PADDING_LENGTH))

# Define message with dynamic padding
MSG				= $(TITLE) $(GPM_FNAME) $(PADDING)$(RESET) ${}
SUCCESS			= $(MSG)$(GREEN)✅ Successfully built! 🚀$(RESET)
SUCCESSB		= $(MSG)$(GREEN)✅ Successfully built bonuses! 🚀$(RESET)

# GPM? end make_art_mk_ansi
# GPM? end make_art_mk

