# **************************************************************************** #
#                                                                              #
#                                                       _    ⣀⣀⣀⡀⡀⡀⡀⣀⡀⣀⣀⣀⡀  #
#    Makefile                                       _ _/ |   ⡇⣶⡆⡇⡾⢏⡭⡵⠀⡇⣶⡆⡇  #
#                                                  | '_| |_  ⣓⣒⠒⡃⡂⣏⡆⡯⢇⠓⠶⠖⡃  #
#    By: elagouch <elagouch@student.42.fr>         |_|_|_(@) ⢻⣊⡞⣪⢳⡗⣳⢤⣈⢍⣰⢖⡇  #
#                                                  | | |_  ) ⠜⡲⡢⣲⡯⡼⡑⡁⣝⣘⡚⢠⠅  #
#    Created: 2024/11/05 15:39:47 by elagouch      |_  _/ /  ⡖⣒⡒⡆⠉⠧⢰⣮⣇⣂⡏⡳⡆  #
#    Updated: 2024/11/18 11:13:41 by elagouch        |_/___| ⣇⣛⣃⡇⡿⢤⠤⠾⠡⠹⢝⣚⡁  #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -Wpedantic -MMD -MP
AR		= ar
ARFLAGS	= rc
RM      = rm -f

SRC =				\
	ft_atoi.c		\
	ft_bzero.c		\
	ft_calloc.c		\
	ft_isalnum.c	\
	ft_isalpha.c	\
	ft_isascii.c	\
	ft_isdigit.c	\
	ft_isprint.c	\
	ft_itoa.c		\
	ft_memchr.c		\
	ft_memcmp.c		\
	ft_memcpy.c		\
	ft_memmove.c	\
	ft_memset.c		\
	ft_putchar_fd.c	\
	ft_putendl_fd.c	\
	ft_putnbr_fd.c	\
	ft_putstr_fd.c	\
	ft_split.c		\
	ft_strdup.c		\
	ft_strrchr.c	\
	ft_strchr.c		\
	ft_striteri.c	\
	ft_strjoin.c	\
	ft_strlcat.c	\
	ft_strlcpy.c	\
	ft_strlen.c		\
	ft_strmapi.c	\
	ft_strnstr.c	\
	ft_strncmp.c	\
	ft_strtrim.c	\
	ft_tolower.c	\
	ft_toupper.c	\
	ft_substr.c
SRC_BONUS =					\
	ft_lstadd_back_bonus.c	\
	ft_lstadd_front_bonus.c	\
	ft_lstclear_bonus.c		\
	ft_lstdelone_bonus.c	\
	ft_lstiter_bonus.c		\
	ft_lstlast_bonus.c		\
	ft_lstmap_bonus.c		\
	ft_lstnew_bonus.c		\
	ft_lstsize_bonus.c 

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
DEP_BONUS = $(SRC_BONUS:.c=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $?

bonus: $(OBJ) $(OBJ_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $?

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP) $(DEP_BONUS)

clean:
	$(RM) $(OBJ) $(OBJ_BONUS) $(DEP) $(DEP_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

