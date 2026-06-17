NAME    = libftprintf.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -MMD -MP
INCLUDE = -I includes -I ../../milestone-0/libft/includes

SRC =	src/ft_printf.c \
	src/parse.c \
	src/printf_signed.c \
	src/printf_hex.c \
	src/printf_str.c \
	src/pfputchar.c \
	src/pfputnbr_base.c \
	src/pfputstr.c \
	src/print_pad.c

BONUS_SRC =	src/ft_printf_bonus.c \
		src/parse.c \
		src/printf_signed.c \
		src/printf_hex.c \
		src/printf_str.c \
		src/pfputchar.c \
		src/pfputnbr_base.c \
		src/pfputstr.c \
		src/print_pad.c \
		src/printf_u_bonus.c \
		src/printf_c_bonus.c

OBJ       = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
DEP       = $(OBJ:.o=.d) $(BONUS_OBJ:.o=.d)

all: $(NAME)

-include $(DEP)

$(NAME): $(OBJ)
	ar rcs $@ $^

bonus: $(BONUS_OBJ)
	ar rcs $(NAME) $^
	@touch bonus

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ) $(DEP) bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
