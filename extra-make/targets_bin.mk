# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_bin.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 16:37:31 by elagouch          #+#    #+#              #
#    Updated: 2025/02/21 11:31:54 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GPM? begin make_targets_bin_mk
$(OBJ): | $(NAME_DEPS_INDIRECT)
$(NAME): $(OBJ)
	@$(ECHO) "$(MSG)🏗️  Building mandatory for $(NAME)\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@$(ECHO) "$(SUCCESS)\n"

.bonus: $(OBJ_BONUS) | $(BNAME_DEPS_INDIRECT)
	@$(ECHO) "$(MSG)🏗️  Building bonuses for $(NAME)\n"
	@$(CC) $(CFLAGS) -o $(BNAME) $^ $(LDFLAGS)
	@$(TOUCH) .bonus
	@$(ECHO) "$(SUCCESSB)\n"
# GPM? end make_targets_bin_mk
