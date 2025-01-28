# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    make_meta.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 14:52:29 by elagouch          #+#    #+#              #
#    Updated: 2025/01/27 22:43:42 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                MAKE METADATA                                 #
# **************************************************************************** #

# GPM? begin make_make_meta
-include $(DEP) $(DEP_BONUS) $(DEP_TEST)
MAKEFLAGS	+= --no-print-directory
.PHONY:		all bonus			clean fclean re title visualize visualizer
.SILENT:	all bonus .bonus	clean fclean re title visualize visualizer
# GPM? end make_make_meta
