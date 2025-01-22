# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_bin_libft_bonus.mk                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:28:53 by elagouch          #+#    #+#              #
#    Updated: 2025/01/22 14:48:06 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #
# GPM? begin make_target_bin_libft_bonus
LIBFT_FLAGS		+= -L$(LIBFT_DIR) -lft

$(LIBFT): $(SRC_LIBFT)
	@$(ECHO) "$(MSG) 🏗️  Building libft\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(ECHO) "$(MSG) 🏗️  Building $(NAME)\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)
	@$(ECHO) "$(SUCCESS)\n"

.bonus: $(OBJ_BONUS) $(LIBFT)
	@$(ECHO) "$(MSG) 🏗️  Building bonuses for $(NAME)\n"
	@$(CC) $(CFLAGS) -o  $(BNAME) $^ $(LIBFT_FLAGS)
	@touch .bonus
	@$(ECHO) "$(SUCCESSB)\n"

clean:
	@$(ECHO) "$(MSG) 🧹 Cleaning the project\n"
	@$(RM) -r $(DIR_OBJ) .title
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(ECHO) "$(MSG) 🧹 Fcleaning the project\n"
	@$(RM) $(NAME) $(BNAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

bonus: .bonus
# GPM? begin make_target_bin_libft_bonus
