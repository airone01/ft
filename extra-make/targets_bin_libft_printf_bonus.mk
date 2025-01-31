# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_bin_libft_printf_bonus.mk                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:28:53 by elagouch          #+#    #+#              #
#    Updated: 2025/01/31 15:35:44 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #
# GPM? begin make_target_bin_libft_bonus
LIBFT_FLAGS		+= -L$(LIBFT_DIR) -lft
PRINTF_FLAGS	+= -L$(PRINTF_DIR) -l:libftprintf.a

$(LIBFT): $(SRC_LIBFT)
	@$(ECHO) "$(MSG)🏗️  Building libft\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(PRINTF): $(SRC_PRINTF)
	@$(ECHO) "$(MSG)🏗️  Building ft_printf\n"
	@$(MAKE) -C $(PRINTF_DIR)

$(NAME): $(OBJ) | $(LIBFT) $(PRINTF)
	@$(ECHO) "$(MSG)🏗️  Building $(NAME)\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS) $(PRINTF_FLAGS)
	@$(ECHO) "$(SUCCESS)\n"

.bonus: $(OBJ_BONUS) $(LIBFT) $(PRINTF)
	@$(ECHO) "$(MSG)🏗️  Building bonuses for $(NAME)\n"
	@$(CC) $(CFLAGS) -o $(BNAME) $^ $(LIBFT_FLAGS) $(PRINTF_FLAGS)
	@touch .bonus
	@$(ECHO) "$(SUCCESSB)\n"

clean:
	@$(ECHO) "$(MSG)🧹 Cleaning the project\n"
	@$(RM) -r $(OUT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	@$(ECHO) "$(MSG)🧹 Fcleaning the project\n"
	@$(RM) $(NAME) $(BNAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean

bonus: .bonus
# GPM? begin make_target_bin_libft_bonus
