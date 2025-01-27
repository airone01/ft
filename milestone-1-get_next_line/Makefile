# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk) # GPM!
# GPM: make_ansi_color_codes
COLOR			= $(COLOR_GET_NEXT_LINE)

# **************************************************************************** #
#                            COMMON ANSI VARIABLES                             #
# **************************************************************************** #

# GPM: make_ansi_color_variables

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	= 1
GPM_NAME	= get_next_line
GPM_FNAME	= $(GPM_MSTONE)-gnl
NAME		= get_next_line.a
OUT_DIR 	= .out/

# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #

include $(realpath ../extra-make/commands.mk) # GPM!
# GPM: make_commands

# **************************************************************************** #
#                                    FLAGS                                     #
# **************************************************************************** #

include $(realpath ../extra-make/flags.mk) # GPM!
# GPM: make_flags
CFLAGS			+= -I$(LIBFT_DIR)

# **************************************************************************** #
#                                    LIBFT                                     #
# **************************************************************************** #

LIBFT_DIR	= $(realpath ../milestone-0-libft)# GPM!
# GPM@ .LIBFT_DIR	= $(realpath ./libft)
LIBFT		= $(LIBFT_DIR)/libft.a

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

_SRC_GNL	=	get_next_line get_next_line_utils
# GPM: make_src_libft
# GPM: make_src_push_swap
include $(realpath ../extra-make/meta.mk) # GPM!
# GPM@ ._SRC_PUSH_SWAP_BONUS	+= $(_SRC_GNL)

# **************************************************************************** #
#                                   MAPPING                                    #
# **************************************************************************** #

SRC_LIBFT	= $(_SRC_LIBFT:%=$(LIBFT_DIR)/%.c)
SRC			= $(_SRC_GNL_BONUS:%=%.c)
SRC_BONUS	= $(_SRC_GNL_BONUS:%=%.c)
OBJ			= $(_SRC_GNL_BONUS:%=$(OUT_DIR)%.o)
DEP			= $(_SRC_GNL_BONUS:%=$(OUT_DIR)%.d)
OBJ_BONUS	= $(_SRC_GNL_BONUS:%=$(OUT_DIR)%.o)
DEP_BONUS	= $(_SRC_GNL_BONUS:%=$(OUT_DIR)%.d)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

include $(realpath ../extra-make/targets_common.mk) # GPM!
# GPM: make_target_common

title:
	@$(ECHO) "$(MSG)             __\n"
	@$(ECHO) "$(MSG)  ___ ____  / /\n"
	@$(ECHO) "$(MSG) / _ \`/ _ \/ /\n"
	@$(ECHO) "$(MSG) \_, /_//_/_/\n"
	@$(ECHO) "$(MSG)/___/\n"
	@$(ECHO) "$(MSG) \n"

include $(realpath ../extra-make/targets_lib_libft.mk) # GPM!
# GPM: make_target_lib_libft
# GPM
checker: $(OBJ) $(OBJ_TEST) $(LIBFT) # GPM
	@$(ECHO) "$(MSG) 🏗️  Building $(NAME)\n" # GPM
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS) # GPM

# **************************************************************************** #
#                                MAKE METADATA                                 #
# **************************************************************************** #

include $(realpath ../extra-make/make_meta.mk) # GPM!
# GPM: make_make_meta
