# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lib_ft_printf.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 22:21:59 by elagouch          #+#    #+#              #
#    Updated: 2025/02/10 20:38:56 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PRINTF_DIR		:= $(realpath ../milestone-1-ft_printf)
# $(call make_lib,PRINTF,ft_printf,libftprintf)

PRINTF_SRC	=	$(_SRC_PRINTF:%=$(PRINTF_DIR)/%.c)
PRINTF		=	$(PRINTF_DIR)/libftprintf.a

# LD
LDFLAGS	:= -L$(PRINTF_DIR) -l:libftprintf.a $(LDFLAGS)
# CC
CFLAGS	+= -I$(PRINTF_DIR)

# Make target config
NAME_DEPS_INDIRECT	+= $(PRINTF)
CLEAN_TARGETS		+= clean_ft_printf
FCLEAN_TARGETS		+= fclean_ft_printf

# Make targets
$(PRINTF): $(PRINTF_SRC)
	@$(ECHO) "$(MSG)🏗️  Building ft_printf\n"
	@$(MAKE) -C $(PRINTF_DIR) BUILD_ENV=$(BUILD_ENV)

clean_ft_printf:
	@$(MAKE) -C $(PRINTF_DIR) clean

fclean_ft_printf:
	@if $(MAKE) -C $(PRINTF_DIR) -n fclean >/dev/null 2>&1; then \
		$(MAKE) -C $(PRINTF_DIR) fclean; \
	fi
