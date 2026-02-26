NAME		:= libasm.a
AR			:= ar
ARFLAGS		:= rcs
AS			:= nasm
ASFLAGS		:= -f elf64 -Wall -Werror
SRC			:= strlen strcpy strcmp write read
SRC			:= $(addsuffix .s,$(addprefix src/ft_,$(SRC)))
OBJ			:= $(SRC:.s=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.s Makefile FORCE
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) ./test

re: fclean
	$(MAKE) all

test: $(NAME)
	$(CC) test.c $(NAME) -o test
	./test

FORCE:

.PHONY: all clean fclean re test FORCE


