# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_lib.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:23:23 by elagouch          #+#    #+#              #
#    Updated: 2025/01/31 15:35:44 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #
# GPM? begin make_target_lib
$(NAME): $(OBJ)
	@$(ECHO) "$(MSG)🏗️  Building $(NAME)\n"
	@$(AR) $(NAME) $^
	@$(ECHO) "$(SUCCESS)\n"

clean:
	@$(ECHO) "$(MSG)🧹 Cleaning the project\n"
	@$(RM) -r $(OUT_DIR)

fclean: clean
	@$(ECHO) "$(MSG)🧹 Fcleaning the project\n"
	@$(RM) $(NAME)
# GPM? end make_target_lib
