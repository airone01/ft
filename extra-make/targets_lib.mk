# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_lib.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 16:37:31 by elagouch          #+#    #+#              #
#    Updated: 2025/02/10 19:06:28 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(NAME): $(OBJ) | $(NAME_DEPS_INDIRECT)
	@$(ECHO) "$(MSG)🏗️  Building mandatory for $(NAME)\n"
	@$(AR) -o $@ $^ $($(NAME)_HEADERS)
	@$(ECHO) "$(SUCCESS)\n"
