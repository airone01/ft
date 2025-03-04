# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    targets_common.mk                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:20:59 by elagouch          #+#    #+#              #
#    Updated: 2025/03/04 18:31:28 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #
# GPM? begin make_targets_common_mk

include $(realpath ../extra-make/commands.mk)# GPM!
# GPM: make_commands_mk

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
# Because MLX doesn't annouce the correct type for an argument
CFLAGS += -Wno-error=cast-function-type

# Default
BUILD_ENV ?= dev
# Set flags based on environment
ifeq ($(BUILD_ENV),debug)
CFLAGS += -O2 -g
else ifeq ($(BUILD_ENV),prod)
CFLAGS += -O2 -march=native -ffunction-sections -fdata-sections -flto -ffast-math
else
# Else: dev mode
CFLAGS += -O1 -g3
endif

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

include $(realpath ../extra-make/sources.mk)# GPM!
# GPM: make_sources_mk

# **************************************************************************** #
#                                   MAPPING                                    #
# **************************************************************************** #

GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)

SRC			:= $(_SRC_$(GPM_MNAME)_MANDATORY:$(SRC_DIR)%=%.c)
SRC_BONUS	:= $(_SRC_$(GPM_MNAME)_BONUS:$(SRC_DIR)%=%.c)
SRC_HEADERS	:= $(_SRC_$(GPM_MNAME)_HEADERS:$(SRC_DIR)%=%.h)
OBJ			:= $(_SRC_$(GPM_MNAME)_MANDATORY:$(SRC_DIR)%=$(OUT_DIR)%.o)
DEP			:= $(_SRC_$(GPM_MNAME)_MANDATORY:$(SRC_DIR)%=$(OUT_DIR)%.d)
OBJ_BONUS	:= $(_SRC_$(GPM_MNAME)_BONUS:$(SRC_DIR)%=$(OUT_DIR)%.o)
DEP_BONUS	:= $(_SRC_$(GPM_MNAME)_BONUS:$(SRC_DIR)%=$(OUT_DIR)%.d)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

$(OUT_DIR):
	@$(MD) $(OUT_DIR)

$(OUT_DIR)%.o: $(SRC_DIR)%.c | Makefile $(OUT_DIR)
	@$(ECHO) "$(MSG)⏳ $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

BNAME_DEPS_INDIRECT = $(NAME_DEPS_INDIRECT)

clean: $(CLEAN_TARGETS)
	@$(ECHO) "$(MSG)🧹 Cleaning the project\n"
	@$(RM) -r $(OUT_DIR)

fclean: clean $(FCLEAN_TARGETS)
	@$(ECHO) "$(MSG)🧹 Fcleaning the project\n"
	@$(RM) $(NAME) $(BNAME)

FORCE:

bonus: .bonus

-include $(DEP) $(DEP_BONUS)
MAKEFLAGS	+= --no-print-directory
.PHONY:		all bonus			clean fclean re title visualize visualizer mandatory check-bonus check-mandatory FORCE
.SILENT:	all bonus .bonus	clean fclean re title visualize visualizer mandatory check-bonus check-mandatory FORCE

re: fclean all
# GPM? end make_targets_common_mk
