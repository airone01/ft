# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk) # GPM!
# GPM: make_ansi_color_codes
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

include $(realpath ../extra-make/lib_libft.mk)

include $(realpath ../extra-make/targets_common.mk) # GPM!
# GPM: make_target_common

include $(realpath ../extra-make/targets_bin.mk)
