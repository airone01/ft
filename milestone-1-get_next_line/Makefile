# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk)# GPM!
# GPM: make_art_mk
COLOR			= $(COLOR_GET_NEXT_LINE)

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	:= 1
GPM_NAME	:= get_next_line
GPM_MNAME	:= GNL
NAME		:= get_next_line.a
BNAME		:= bget_next_line.a
OUT_DIR 	:= .out/

# **************************************************************************** #
#                                    LIBS                                      #
# **************************************************************************** #

LIBFT_DIR		:= $(realpath ../milestone-0-libft)
# GPM@	.LIBFT_DIR	= $(realpath ../libft)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: title $(NAME)

title:
	@$(ECHO) "$(MSG)             __\n"
	@$(ECHO) "$(MSG)  ___ ____  / /\n"
	@$(ECHO) "$(MSG) / _ \`/ _ \/ /\n"
	@$(ECHO) "$(MSG) \_, /_//_/_/\n"
	@$(ECHO) "$(MSG)/___/\n"
	@$(ECHO) "$(MSG)\n"

include $(realpath ../extra-make/lib_libft.mk)# GPM!
# GPM: make_lib_libft_mk

# GPM: make_sources_mk

# GPM: make_commands_mk

include $(realpath ../extra-make/targets_common.mk)# GPM!
# GPM: make_targets_common_mk

include $(realpath ../extra-make/targets_lib.mk)# GPM!
# GPM: make_targets_lib_mk
