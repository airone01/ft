# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_lib.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 16:37:31 by elagouch          #+#    #+#              #
#    Updated: 2025/03/06 12:20:31 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GPM? begin make_targets_lib_mk
$(NAME): $(OBJ) | $(NAME_DEPS_INDIRECT)
	@$(MAKE) title
	@$(ECHO) "$(MSG)🏗️  Building mandatory for $(NAME)\n"
	@$(AR) $@ $^ $($(NAME)_HEADERS)
	@$(ECHO) "$(SUCCESS)\n"
# GPM? end make_targets_lib_mk
