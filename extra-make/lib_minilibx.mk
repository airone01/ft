# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lib_minilibx.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 22:21:59 by elagouch          #+#    #+#              #
#    Updated: 2025/03/04 15:28:14 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GPM? begin make_lib_minilibx_mk
# **************************************************************************** #
#                               lib_minilibx.mk                                #
# **************************************************************************** #

MINILIBX_SRC	=	$(_SRC_MINILIBX:%=$(MINILIBX_DIR)/%.c)
MINILIBX		=	$(MINILIBX_DIR)/libmlx_Linux.a

# LD
LDFLAGS	:= -L$(MINILIBX_DIR) -lm -lmlx -lXext -lX11 $(LDFLAGS)
# CC
CFLAGS	+= -I$(MINILIBX_DIR)

# Make target config
NAME_DEPS_INDIRECT	+= $(MINILIBX)
CLEAN_TARGETS		+= clean_minilibx
FCLEAN_TARGETS		+= fclean_minilibx

# Make targets
$(MINILIBX): FORCE
	@$(ECHO) "$(MSG)🏗️  Building minilibx\n"
	@$(MAKE) -sC $(MINILIBX_DIR) BUILD_ENV=$(BUILD_ENV)

clean_minilibx:
	@$(MAKE) -sC $(MINILIBX_DIR) clean

fclean_minilibx:
	@if $(MAKE) -sC $(MINILIBX_DIR) -n fclean >/dev/null 2>&1; then \
		$(MAKE) -sC $(MINILIBX_DIR) fclean; \
	fi
# GPM? end make_lib_minilibx_mk
