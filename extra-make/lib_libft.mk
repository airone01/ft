# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lib_libft.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 22:21:59 by elagouch          #+#    #+#              #
#    Updated: 2025/05/12 02:03:01 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GPM? begin make_lib_libft_mk
# **************************************************************************** #
#                                 lib_libft.mk                                 #
# **************************************************************************** #

LIBFT_SRC	=	$(_SRC_LIBFT:%=$(LIBFT_DIR)/%.c)
LIBFT		=	$(LIBFT_DIR)/libft.a

# LD
LDFLAGS	:= -L$(LIBFT_DIR) -l:libft.a $(LDFLAGS)
# CC
CFLAGS	+= -I$(LIBFT_DIR)/includes

# Make target config
NAME_DEPS_INDIRECT	+= $(LIBFT)
CLEAN_TARGETS		+= clean_libft
FCLEAN_TARGETS		+= fclean_libft

# Make targets
$(LIBFT): FORCE
	@$(ECHO) "$(MSG)🏗️  Building libft\n"
	@$(MAKE) -sC $(LIBFT_DIR) BUILD_ENV=$(BUILD_ENV)

FORCE:

clean_libft:
	@$(MAKE) -sC $(LIBFT_DIR) clean

fclean_libft:
	@if $(MAKE) -sC $(LIBFT_DIR) -n fclean >/dev/null 2>&1; then \
		$(MAKE) -sC $(LIBFT_DIR) fclean; \
	fi
# GPM? end make_lib_libft_mk
