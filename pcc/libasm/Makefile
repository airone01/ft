NAME		:= libasm.a
AR			:= ar
ARFLAGS		:= rcs
AS			:= nasm
ASFLAGS		:= -f elf64 -Wall -Werror
SRC			:= strlen strcpy strcmp write read strdup
SRCB		:= atoi_base list_push_front list_size list_sort list_remove_if
SRC			+= $(addsuffix _bonus,$(SRCB))
SRC			:= $(addsuffix .s,$(addprefix src/ft_,$(SRC)))
OBJ			:= $(SRC:.s=.o)

BONUS_SRC	:= $(addprefix src/ft_list_,push_front_bonus.s size_bonus.s sort_bonus.s remove_if_bonus.s)
BONUS_OBJ	:= $(BONUS_SRC:.s=.o)

TNAME		:= test
TSRC		:= test.c
# This tells the linker to create the ELF section and explicitly mark it as
# non-executable and non-allocating. Not including a '.note.GNU-stack' section
# in the assembly code implies executable stack.
TLDFLAGS	:= -Wl,-z,noexecstack

all: $(NAME)

bonus: $(NAME) $(BONUS_OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(BONUS_OBJ)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.s Makefile FORCE
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME) $(TNAME)

re: fclean
	$(MAKE) all

$(TNAME): $(NAME)
	$(CC) $(TSRC) $(TLDFLAGS) $(NAME) -o $(TNAME)

FORCE:

.PHONY: all bonus clean fclean re test FORCE
