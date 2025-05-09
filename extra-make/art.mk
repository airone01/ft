# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    art.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:45:02 by elagouch          #+#    #+#              #
#    Updated: 2025/05/09 15:07:50 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

# GPM? begin make_art_mk
# Common core projects
COLOR_FT			= 138;35;135
COLOR_LIBFT			= 145;44;132
COLOR_B2BR			= 151;51;128
COLOR_FT_PRINTF		= 158;58;124
COLOR_GET_NEXT_LINE	= 165;64;120
COLOR_PUSH_SWAP		= 173;70;115
COLOR_PIPEX			= 180;75;110
COLOR_FDF			= 195;85;99
COLOR_MINISHELL		= 203;90;92
COLOR_PHILO			= 210;95;85

# result of ./gradient.sh #8A2387 #F27121 15 -v

# 138;35;135
# 145;44;132
# 151;51;128
# 158;58;124
# 165;64;120
# 173;70;115
# 180;75;110
# 187;80;105
# 195;85;99
# 203;90;92
# 210;95;85

# 218;100;76
# 226;104;66

# 234;109;53
# 242;113;33


# Extra projects
COLOR_MINECRAFT		= 234;109;53
COLOR_ARTHUR		= 242;113;33

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

# GPM? end make_art_mk
