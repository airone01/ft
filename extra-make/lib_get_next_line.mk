# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lib_get_next_line.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 22:21:59 by elagouch          #+#    #+#              #
#    Updated: 2025/02/05 17:02:58 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GNL_DIR		:= $(realpath ../milestone-1-get_next_line)
# $(call make_lib,GNL,get_next_line,get_next_line)

GNL_SRC	=	$(_SRC_GNL:%=$(GNL_DIR)/%.c)
GNL		=	$(GNL_DIR)/get_next_line.a

# LD
LDLAGS	+= -L$(GNL_DIR) -l:get_next_line.a
# CC
CFLAGS	+= -I$(GNL_DIR)

# Make target config
NAME_DEPS_INDIRECT	+= $(GNL)
CLEAN_TARGETS		+= clean_get_next_line
FCLEAN_TARGETS		+= fclean_get_next_line

# Make targets
$(GNL): $(GNL_SRC)
	@$(ECHO) "$(MSG)🏗️  Building get_next_line\n"
	@$(MAKE) -C $(GNL_DIR) BUILD_ENV=$(BUILD_ENV)

clean_get_next_line:
	@$(MAKE) -C $(GNL_DIR) clean

fclean_get_next_line:
	@if $(MAKE) -C $(GNL_DIR) -n fclean >/dev/null 2>&1; then \
		$(MAKE) -C $(GNL_DIR) fclean; \
	fi
