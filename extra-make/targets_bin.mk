# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_bin.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 16:37:31 by elagouch          #+#    #+#              #
#    Updated: 2025/02/10 19:09:59 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(OBJ): | $(NAME_DEPS_INDIRECT)
$(NAME): $(OBJ)
	@$(ECHO) "$(MSG)🏗️  Building mandatory for $(NAME)\n"
	@echo "OBJ IS '$(OBJ)'"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@$(ECHO) "$(SUCCESS)\n"

$(BNAME): $(OBJ_BONUS) | $(BNAME_DEPS_INDIRECT)
	@$(ECHO) "$(MSG)🏗️  Building bonuses for $(NAME)\n"
	@$(CC) $(CFLAGS) -o $(BNAME) $^
	@touch .bonus
	@$(ECHO) "$(SUCCESSB)\n"
