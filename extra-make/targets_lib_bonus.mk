# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_lib_bonus.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:23:23 by elagouch          #+#    #+#              #
#    Updated: 2025/01/27 22:41:37 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #
# GPM? begin make_target_lib_bonus
$(NAME): $(OBJ)
	@$(ECHO) "$(MSG) 🏗️  Building $(NAME)\n"
	@$(AR) $(NAME) $^
	@$(ECHO) "$(SUCCESS)\n"

.bonus: $(OBJ) $(OBJ_BONUS)
	@$(ECHO) "$(MSG) 🏗️  Building bonuses of $(NAME)\n"
	@$(AR) $(NAME) $^
	@touch .bonus
	@$(ECHO) "$(SUCCESSB)\n"

bonus: .bonus

clean:
	@$(ECHO) "$(MSG) 🧹 Cleaning the project\n"
	@$(RM) -r $(OUT_DIR)

fclean: clean
	@$(ECHO) "$(MSG) 🧹 Fcleaning the project\n"
	@$(RM) $(NAME)
# GPM? end make_target_lib_bonus
