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
_SRC			=			\
	ft_atoi					\
	ft_abs					\
	ft_bzero				\
	ft_calloc				\
	ft_isalnum				\
	ft_isalpha				\
	ft_isascii				\
	ft_isdigit				\
	ft_isprint				\
	ft_itoa					\
	ft_memchr				\
	ft_memcmp				\
	ft_memcpy				\
	ft_memmove				\
	ft_memset				\
	ft_putchar_fd			\
	ft_putendl_fd			\
	ft_putnbr_fd			\
	ft_putstr_fd			\
	ft_split				\
	ft_strdup				\
	ft_strrchr				\
	ft_strchr				\
	ft_strcmp				\
	ft_striteri				\
	ft_strjoin				\
	ft_strlcat				\
	ft_strlcpy				\
	ft_strlen				\
	ft_strmapi				\
	ft_strnstr				\
	ft_strncmp				\
	ft_strtrim				\
	ft_tolower				\
	ft_toupper				\
	ft_substr
_SRC_BONUS	=				\
	ft_lstadd_back_bonus	\
	ft_lstadd_front_bonus	\
	ft_lstclear_bonus		\
	ft_lstdelone_bonus		\
	ft_lstiter_bonus		\
	ft_lstlast_bonus		\
	ft_lstmap_bonus			\
	ft_lstnew_bonus			\
	ft_lstsize_bonus

# ------------ Mapping -----------
OBJ			= $(_SRC:%=$(DIR_OBJ)%.o)
DEP			= $(_SRC:%=$(DIR_OBJ)%.d)
OBJ_BONUS	= $(_SRC_BONUS:%=$(DIR_OBJ)%.o)
DEP_BONUS	= $(_SRC_BONUS:%=$(DIR_OBJ)%.d)

# ------------ Targets -----------
all: $(NAME)

$(NAME): $(OBJ)
	@$(ECHO) "$(MSG) 🏗️  Building $(NAME)\n"
	@$(AR) $(ARFLAGS) $(NAME) $?
	@$(ECHO) "$(SUCCESS)\n"

.bonus: $(OBJ) $(OBJ_BONUS)
	@$(ECHO) "$(MSG) 🏗️  Building bonuses lib\n"
	@$(AR) $(ARFLAGS) $(NAME) $?
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
