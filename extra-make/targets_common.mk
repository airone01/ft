# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_common.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:20:59 by elagouch          #+#    #+#              #
#    Updated: 2025/02/05 17:05:24 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GPM? begin make_target_common
# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #

include $(realpath ../extra-make/commands.mk)
# GPM: make_commands

# Standard compilation checks
CFLAGS	+= -Wall -Werror -Wextra
# Compability checks
CFLAGS	+= -Wpedantic
# Self-explanatory
CFLAGS	+= -Wno-unused-result
# Dependency management
CFLAGS	+= -MD -MP
# Warns when a variable declaration shadows another variable
CFLAGS	+= -Wshadow
# More thorough than -Wunused-result
CFLAGS	+= -Wunused
# Implicit conversions that may change value
CFLAGS	+= -Wconversion
# Implicit conversions between signed and un signed
CFLAGS	+= -Wsign-conversion
# Disables pointer arithmetics
# (no `*ptr++`)
CFLAGS	+= -Wpointer-arith
# Catches more printf/scanf format mismatches
CFLAGS	+= -Wformat=2
# Warns about == for floats which is sus
CFLAGS	+= -Wfloat-equal
# Makes strings const char*
# Can break old code but meh fuck it
CFLAGS	+= -Wwrite-strings
# Keeps the frame pointer in registers
# Minor performance cost
CFLAGS	+= -fno-omit-frame-pointer
ifeq ($(CC),gcc)
# Kinda important but not in CC by default
CFLAGS	+= -Wstringop-truncation
endif

# Default
BUILD_ENV ?= dev
# Set flags based on environment
ifeq ($(BUILD_ENV),debug)
CFLAGS += -O2 -g
else ifeq ($(BUILD_ENV),prod)
CFLAGS += -O2 -march=native -ffunction-sections -fdata-sections
else
# Else: dev mode
CFLAGS += -O0 -g3 -fsanitize=address,undefined
endif

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

# GPM: make_src
include $(realpath ../extra-make/sources.mk) # GPM!

# **************************************************************************** #
#                                   MAPPING                                    #
# **************************************************************************** #

GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)

SRC			:= $(_SRC_$(GPM_MNAME)_MANDATORY:%=%.c)
SRC_BONUS	:= $(_SRC_$(GPM_MNAME)_BONUS:%=%.c)
SRC_HEADERS	:= $(_SRC_$(GPM_MNAME)_HEADERS:%=%.h)
OBJ			:= $(_SRC_$(GPM_MNAME)_MANDATORY:%=$(OUT_DIR)%.o)
DEP			:= $(_SRC_$(GPM_MNAME)_MANDATORY:%=$(OUT_DIR)%.d)
OBJ_BONUS	:= $(_SRC_$(GPM_MNAME)_BONUS:%=$(OUT_DIR)%.o)
DEP_BONUS	:= $(_SRC_$(GPM_MNAME)_BONUS:%=$(OUT_DIR)%.d)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

$(OUT_DIR):
	@$(MD) $(OUT_DIR)

$(OUT_DIR)%.o: %.c | Makefile $(OUT_DIR)
	@$(ECHO) "$(MSG)⏳ $@\n"
	$(CC) $(CFLAGS) -c $< -o $@

BNAME_DEPS_INDIRECT = $(NAME_DEPS_INDIRECT)

clean: $(CLEAN_TARGETS)
	@$(ECHO) "$(MSG)🧹 Cleaning the project\n"
	@$(RM) -r $(OUT_DIR)

fclean: clean $(FCLEAN_TARGETS)
	@$(ECHO) "$(MSG)🧹 Fcleaning the project\n"
	@$(RM) $(NAME) $(BNAME)

# $(info $(call make_lib,LIBFT,libft,libft))

bonus: $(BNAME)

-include $(DEP) $(DEP_BONUS)
MAKEFLAGS	+= --no-print-directory
.PHONY:		all bonus			clean fclean re title visualize visualizer
.SILENT:	all bonus .bonus	clean fclean re title visualize visualizer

re: fclean all
# GPM? end make_target_common
