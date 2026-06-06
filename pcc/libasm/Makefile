NAME		:= libasm.a
AR			:= ar
ARFLAGS		:= rcs
AS			:= nasm
ASFLAGS		:= -f elf64 -Wall -Werror

SRC			:= strlen strcpy strcmp write read strdup
SRC			:= $(addsuffix .s,$(addprefix src/ft_,$(SRC)))
OBJ			:= $(SRC:.s=.o)

SRCB		:= atoi_base list_push_front list_size list_sort list_remove_if
SRCB		:= $(addsuffix _bonus.s,$(addprefix src/ft_,$(SRCB)))
OBJB		:= $(SRCB:.s=.o)

TNAME		:= test
TSRC		:= test.c
# This tells the linker to create the ELF section and explicitly mark it as
# non-executable and non-allocating. Not including a '.note.GNU-stack' section
# in the assembly code implies executable stack.
TLDFLAGS	:= -Wl,-z,noexecstack

all: $(NAME)

bonus: $(NAME) $(OBJB)
	$(AR) $(ARFLAGS) $(NAME) $(OBJB)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.s Makefile FORCE
	$(AS) $(ASFLAGS) $< -o $@

clean:
	$(RM) $(OBJ) $(OBJB)

fclean: clean
	$(RM) $(NAME) $(TNAME)

re: fclean
	$(MAKE) all

$(TNAME): bonus $(NAME)
	$(CC) $(TSRC) $(TLDFLAGS) $(NAME) -o $(TNAME)

FORCE:

.PHONY: all bonus clean fclean re test FORCE
