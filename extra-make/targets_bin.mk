# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_bin.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 16:37:31 by elagouch          #+#    #+#              #
#    Updated: 2025/02/05 17:24:39 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(OBJ): | $(NAME_DEPS_INDIRECT)
$(NAME): $(OBJ)
	@$(ECHO) "$(MSG)🏗️  Building mandatory for $(NAME)\n"
	@$(ECHO) "$(MSG)🏗️  Indr deps are $(NAME_DEPS_INDIRECT)\n"
	@$(ECHO) "$(MSG)🏗️  Objs are $(OBJ)\n"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@$(ECHO) "$(SUCCESS)\n"

$(BNAME): $(OBJ_BONUS) | $(BNAME_DEPS_INDIRECT)
	@$(ECHO) "$(MSG)🏗️  Building bonuses for $(NAME)\n"
	@$(CC) $(CFLAGS) -o $(BNAME) $^
	@touch .bonus
	@$(ECHO) "$(SUCCESSB)\n"
