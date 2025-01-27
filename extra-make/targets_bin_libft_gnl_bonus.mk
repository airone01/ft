# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_bin_libft_gnl_bonus.mk                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:28:53 by elagouch          #+#    #+#              #
#    Updated: 2025/01/23 15:54:36 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #
# GPM? begin make_target_bin_libft_gnl_bonus
LIBFT_FLAGS		+= -L$(LIBFT_DIR) -lft
GNL_FLAGS		+= -L$(GNL_DIR) -l:get_next_line.a

$(LIBFT): $(SRC_LIBFT)
	@$(ECHO) "$(MSG) 🏗️  Building libft\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(GNL): $(SRC_GNL)
	@$(ECHO) "$(MSG) 🏗️  Building get_next_line\n"
	@$(MAKE) -C $(GNL_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(ECHO) "$(MSG) 🏗️  Building $(NAME)\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS)
	@$(ECHO) "$(SUCCESS)\n"

.bonus: $(OBJ_BONUS) $(LIBFT) $(GNL)
	@$(ECHO) "$(MSG) 🏗️  Building bonuses for $(NAME)\n"
	@$(CC) $(CFLAGS) -o $(BNAME) $^ $(GNL_FLAGS) $(LIBFT_FLAGS)
	@touch .bonus
	@$(ECHO) "$(SUCCESSB)\n"

clean:
	@$(ECHO) "$(MSG) 🧹 Cleaning the project\n"
	@$(RM) -r $(OUT_DIR) .title
	@$(MAKE) -C $(GNL_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(ECHO) "$(MSG) 🧹 Fcleaning the project\n"
	@$(RM) $(NAME) $(BNAME)
	@$(MAKE) -C $(GNL_DIR) fclean
	@$(MAKE) -C $(LIBFT_DIR) fclean

bonus: .bonus
# GPM? begin make_target_bin_libft_gnl_bonus
