# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_lib_libft.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:23:23 by elagouch          #+#    #+#              #
#    Updated: 2025/01/27 15:19:31 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #
# GPM? begin make_target_lib_libft
LIBFT_FLAGS		+= -L$(LIBFT_DIR) -lft

$(LIBFT):
	@$(ECHO) "$(MSG) 🏗️  Building libft\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) | $(LIBFT)
	@$(ECHO) "$(MSG) 🏗️  Building $(NAME)\n"
	@$(AR) $(NAME) $?
	@$(ECHO) "$(SUCCESS)\n"

clean:
	@$(ECHO) "$(MSG) 🧹 Cleaning the project\n"
	@$(RM) -r $(OUT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(ECHO) "$(MSG) 🧹 Fcleaning the project\n"
	@$(RM) $(NAME) .title
	@$(MAKE) -C $(LIBFT_DIR) fclean
# GPM? end make_target_lib_libft
