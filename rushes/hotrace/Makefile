# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/22 10:17:11 by anfichet          #+#    #+#              #
#    Updated: 2025/03/20 13:47:00 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = hotrace

# *********************************VARIABLES**************************************** #

SRCS_DIR = ./

SRCS_LST= \
		error.c \
		free_2d_array.c \
		get_next_line.c \
		get_next_line_utils.c \
		hash_find_index.c \
		hash_fnv1a.c \
		libft_utils.c \
		libft_utils_str.c \
		lst_utils.c \
		main.c \
		parse_content.c \
		print_utils.c \
		parse_content_utils.c \
		tbl_clear.c \
		tbl_utils.c \
		files_utils.c \
		files_utils2.c \
		process_utils.c \


SRCS := $(addprefix $(SRCS_DIR), $(SRCS_LST))


OBJS_DIR = ./.objs/
OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

INCS = ./


DEPS = $(OBJS:.o=.d)

# **********************************COMMANDS**************************************** #

CC = cc

CFLAGS := -Werror -Wextra -Wall -Ofast
# DEV MODE
#CFLAGS += -g3

CPPFLAGS = $(addprefix -I, $(dir $(INCS))) -MMD -MP

LDFLAGS = $(addprefix -L, $(dir $(LIBS_PATH)))
LDLIBS =  $(addprefix -l, $(LIBS_TARGET))

RM = rm -rf

DIR_DUP = mkdir -p $(@D)

AR = ar rcs

MAKEFLAGS += --no-print-directory

# **********************************RULES**************************************** #

.PHONY: all
all: $(NAME)

-include $(DEPS)

$(NAME): $(LIBS_PATH) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)


$(LIBS_PATH): FORCE
	@echo " "
	@echo "\033[1m\033[35m#-------------------------[COMPILATION LIBS]-------------------------#\033[0m"
	$(MAKE) -C $(@D)
	@echo "\033[1m\033[35m#---------------------------[LIBS COMPILED]--------------------------#\033[0m"
	@echo " "


$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean :
	$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean : clean
	$(RM) $(NAME)

.PHONY: re
re : fclean all

.PHONY: FORCE
FORCE:
