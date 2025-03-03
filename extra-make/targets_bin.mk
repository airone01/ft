# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_bin.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 16:37:31 by elagouch          #+#    #+#              #
#    Updated: 2025/03/03 21:43:19 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GPM? begin make_targets_bin_mk
$(OBJ): | $(NAME_DEPS_INDIRECT)

$(NAME): $(OBJ) | check-bonus
	@$(MAKE) title
	@$(ECHO) "$(MSG)🏗️  Building mandatory for $(NAME)\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@$(ECHO) "$(SUCCESS)\n"

check-bonus:
	@if [ -f .bonus ]; then \
		$(RM) -f .bonus; \
		$(RM) -f $(NAME); \
	fi

.bonus: $(OBJ_BONUS) | $(BNAME_DEPS_INDIRECT) check-mandatory
	@$(MAKE) title
	@$(ECHO) "$(MSG)🏗️  Building bonuses for $(NAME)\n"
	@$(CC) $(CFLAGS) -o $(BNAME) $^ $(LDFLAGS)
	@$(TOUCH) .bonus
	@$(ECHO) "$(SUCCESSB)\n"

check-mandatory:
	@if [ -f $(NAME) ]; then \
		$(RM) -f $(NAME); \
	fi

bonus: .bonus
# GPM? end make_targets_bin_mk
