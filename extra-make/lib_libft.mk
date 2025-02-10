# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lib_libft.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 22:21:59 by elagouch          #+#    #+#              #
#    Updated: 2025/02/10 20:39:07 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $(call make_lib,LIBFT,libft,libft)
# $(info $(call make_lib,LIBFT,libft,libft))

LIBFT_SRC	=	$(_SRC_LIBFT:%=$(LIBFT_DIR)/%.c)
LIBFT		=	$(LIBFT_DIR)/libft.a

# LD
LDFLAGS	:= -L$(LIBFT_DIR) -l:libft.a $(LDFLAGS)
# CC
CFLAGS	+= -I$(LIBFT_DIR)

# Make target config
NAME_DEPS_INDIRECT	+= $(LIBFT)
CLEAN_TARGETS		+= clean_libft
FCLEAN_TARGETS		+= fclean_libft

# Make targets
$(LIBFT): $(LIBFT_SRC)
	@$(ECHO) "$(MSG)🏗️  Building libft\n"
	@$(MAKE) -C $(LIBFT_DIR) BUILD_ENV=$(BUILD_ENV)

clean_libft:
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean_libft:
	@if $(MAKE) -C $(LIBFT_DIR) -n fclean >/dev/null 2>&1; then \
		$(MAKE) -C $(LIBFT_DIR) fclean; \
	fi
