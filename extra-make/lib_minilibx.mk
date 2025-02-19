# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lib_minilibx.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 22:21:59 by elagouch          #+#    #+#              #
#    Updated: 2025/02/19 17:25:39 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# MINILIBX_DIR		:= $(realpath ../other-minilibx)
# $(call make_lib,MINILIBX,minilibx,libmlx_Linux)

MINILIBX_SRC	=	$(_SRC_MINILIBX:%=$(MINILIBX_DIR)/%.c)
MINILIBX		=	$(MINILIBX_DIR)/libmlx_Linux.a

# LD
LDFLAGS	:= -L$(MINILIBX_DIR) -l:libmlx_Linux.a $(LDFLAGS) -lz -lX11 -lXext
# CC
CFLAGS	+= -I$(MINILIBX_DIR)

# Make target config
NAME_DEPS_INDIRECT	+= $(MINILIBX)
CLEAN_TARGETS		+= clean_minilibx
FCLEAN_TARGETS		+= fclean_minilibx

# Make targets
$(MINILIBX): $(MINILIBX_SRC)
	@$(ECHO) "$(MSG)🏗️  Building minilibx\n"
	@$(MAKE) -C $(MINILIBX_DIR) BUILD_ENV=$(BUILD_ENV)

clean_minilibx:
	@$(MAKE) -C $(MINILIBX_DIR) clean

fclean_minilibx:
	@if $(MAKE) -C $(MINILIBX_DIR) -n fclean >/dev/null 2>&1; then \
		$(MAKE) -C $(MINILIBX_DIR) fclean; \
	fi
