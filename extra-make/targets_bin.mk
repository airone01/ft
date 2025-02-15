# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_bin.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 16:37:31 by elagouch          #+#    #+#              #
#    Updated: 2025/02/10 20:24:40 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(OBJ): | $(NAME_DEPS_INDIRECT)
$(NAME): $(OBJ)
	@$(ECHO) "$(MSG)🏗️  Building mandatory for $(NAME)\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@$(ECHO) "$(SUCCESS)\n"

$(BNAME): $(OBJ_BONUS) | $(BNAME_DEPS_INDIRECT)
	@$(ECHO) "$(MSG)🏗️  Building bonuses for $(NAME)\n"
	@$(CC) $(CFLAGS) -o $(BNAME) $^ $(LDFLAGS)
	@touch .bonus
	@$(ECHO) "$(SUCCESSB)\n"
