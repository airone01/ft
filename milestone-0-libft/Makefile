# ------------- ANSI -------------
TITLE		= \033[48;5;78;30;1m
RESET		= \033[0m
GREEN		= \033[1;32m
MSG			= $(TITLE) $(GPM_FNAME) \t$(RESET)
SUCCESS		= $(MSG) $(GREEN)✅ Successfully built! 🚀$(RESET)
SUCCESSB	= $(MSG) $(GREEN)✅ Successfully built bonuses! 🚀$(RESET)

# ------------- Meta -------------
GPM_MSTONE	= 0
GPM_NAME	= libft
GPM_FNAME	= $(GPM_MSTONE)-$(GPM_NAME)
NAME		= libft.a
DIR_OBJ 	= .obj/

# ----------- Commands -----------
ECHO		= printf
CC			= cc
AR			= ar
RM      	= rm -f
MD			= mkdir -p

# ------------- Flags ------------
CFLAGS		= -Wall -Werror -Wextra -Wpedantic -MD -MP
ARFLAGS		= rcs

# ------------ Sources -----------
SRC			=		\
	ft_atoi.c		\
	ft_abs.c        \
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
	ft_strcmp.c		\
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
SRC_BONUS	=				\
	ft_lstadd_back_bonus.c	\
	ft_lstadd_front_bonus.c	\
	ft_lstclear_bonus.c		\
	ft_lstdelone_bonus.c	\
	ft_lstiter_bonus.c		\
	ft_lstlast_bonus.c		\
	ft_lstmap_bonus.c		\
	ft_lstnew_bonus.c		\
	ft_lstsize_bonus.c

# ------------ Mapping -----------
OBJ			= $(SRC:%.c=$(DIR_OBJ)%.o)
DEP			= $(SRC:%.c=$(DIR_OBJ)%.d)
OBJ_BONUS	= $(SRC_BONUS:%.c=$(DIR_OBJ)%.o)
DEP_BONUS	= $(SRC_BONUS:%.c=$(DIR_OBJ)%.d)

# ------------ Targets -----------
all: $(NAME)

$(NAME): $(OBJ)
	@$(ECHO) "$(MSG) ⏳ Building $(NAME)\n"
	@$(AR) $(ARFLAGS) $(NAME) $?
	@$(ECHO) "$(SUCCESS)\n"

.bonus: $(OBJ) $(OBJ_BONUS)
	@$(ECHO) "$(MSG) ⏳ Building bonuses lib\n"
	$(AR) $(ARFLAGS) $(NAME) $?
	@touch .bonus
	@$(ECHO) "$(SUCCESSB)\n"

bonus: .bonus # Temp file to avoid unnecessary rebuilds

$(DIR_OBJ)%.o: %.c Makefile
	@$(MD) $(DIR_OBJ)
	@$(ECHO) "$(MSG) ⏳ $@\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(ECHO) "$(MSG) 🧹 Cleaning the project\n"
	@$(RM) -r $(DIR_OBJ)

fclean: clean
	@$(ECHO) "$(MSG) 🧹 Fcleaning the project\n"
	@$(RM) $(NAME)

re: fclean all

# ----------- Make meta ----------
MAKEFLAGS	+= --no-print-directory
-include $(DEP) $(DEP_BONUS)
.PHONY: all bonus clean fclean re
.SILENT: clean fclean
