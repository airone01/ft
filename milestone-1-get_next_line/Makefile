# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 09:27:02 by elagouch          #+#    #+#              #
#    Updated: 2024/11/29 11:49:54 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------- ANSI -------------
TITLE_SEC	= \033[48;5;78;30;1m
RESET		= \033[0m

# ------------- Meta -------------
GPM_MSTONE	= 1
GPM_NAME	= get_next_line
GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)
NAME		= gnl
DIR_OBJ 	= .obj/

# ----------- Commands -----------
ECHO		= echo
CC			= cc
AR			= ar
RM      	= rm -f
MD			= mkdir -p

# ------------- Flags ------------
CFLAGS		= -Wall -Werror -Wextra -Wpedantic -MMD -MP -g3 -D BUFFER_SIZE=2048
ARFLAGS		= rcs

# ------------ Sources -----------
SRC			=				\
	get_next_line.c			\
	get_next_line_utils.c	\
	test2.c
SRC_BONUS	=

# ------------ Mapping -----------
OBJ			= $(SRC:%.c=$(DIR_OBJ)%.o)
DEP			= $(SRC:%.c=$(DIR_OBJ)%.d)
OBJ_BONUS	= $(SRC_BONUS:%.c=$(DIR_OBJ)%.o)
DEP_BONUS	= $(SRC_BONUS:%.c=$(DIR_OBJ)%.d)

# ------------ Targets -----------
all: $(NAME)

$(NAME): $(OBJ)
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Building lib"
	$(CC) $(CFLAGS) -o $(NAME) $?

.bonus: $(OBJ) $(OBJ_BONUS)
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Building bonuses lib"
	$(CC) $(CFLAGS) -o $(NAME) $?
	@touch .bonus

bonus: .bonus # Temp file to avoid unnecessary rebuilds

$(DIR_OBJ)%.o: %.c Makefile
	@$(MD) $(DIR_OBJ)
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)... $@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Cleaning the project"
	@$(RM) -r $(DIR_OBJ) empty.txt single.txt multiple.txt no_newline.txt large.txt mixed.txt binary.txt test1.txt test2.txt huge.txt

fclean: clean
	@$(ECHO) "$(TITLE_SEC) $(GPM_FNAME) \t$(RESET)Fcleaning the project"
	@$(RM) $(NAME)

re: fclean all

# ----------- Make meta ----------
MAKEFLAGS	+= --no-print-directory
-include $(DEP) $(DEP_BONUS)
.PHONY: all bonus clean fclean re
.SILENT: clean fclean
