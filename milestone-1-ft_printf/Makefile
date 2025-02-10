# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ../extra-make/art.mk) # GPM!
COLOR			= $(COLOR_FT_PRINTF)

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_MSTONE	:= 1
GPM_NAME	:= ft_printf
GPM_MNAME	:= PRINTF
NAME		:= libftprintf.a
BNAME		:= blibftprintf.a
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
	@$(ECHO) "$(MSG)   _____               _      __  ___\n"
	@$(ECHO) "$(MSG)  / _/ /_    ___  ____(_)__  / /_/ _/\n"
	@$(ECHO) "$(MSG) / _/ __/   / _ \/ __/ / _ \\/ __/ _/\n"
	@$(ECHO) "$(MSG)/_/ \__/___/ .__/_/ /_/_//_/\\__/_/\n"
	@$(ECHO) "$(MSG)      /___/_/\n"
	@$(ECHO) "$(MSG)\n"

include $(realpath ../extra-make/lib_libft.mk)

include $(realpath ../extra-make/targets_common.mk) # GPM!
# GPM: make_target_common

include $(realpath ../extra-make/targets_bin.mk)
