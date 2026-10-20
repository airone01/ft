ifndef VERBOSE
MAKEFLAGS += --silent
.SILENT:
endif

NAME := libb.a
B := ../B

SRC := char close ctime getchar lchar open putchar printf printn read write
SRC := $(addsuffix .b, $(SRC))
ASM := $(SRC:.b=.s)
OBJ := $(SRC:.b=.o)

AR := ar
ARFLAGS := rcs

AS := as
ASFLAGS := --32

REDHB := \e[1;101;30m
GRNHB := \e[1;102;30m
BLUHB := \e[1;104;30m
CRESET := \e[0m

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(GRNHB) AR $(CRESET) $^\n"
	@$(AR) $(ARFLAGS) $@ $^
	@printf "$(GRNHB)    $(CRESET) $@\n"

%.o: %.s
	@printf "$(REDHB) AS $(CRESET) $<\n"
	@$(AS) $(ASFLAGS) $< -o $@

%.s: %.b
	@printf "$(BLUHB) BC $(CRESET) $<\n"
	@$(B) < $< > $@

clean:
	@rm -fv $(OBJ) $(ASM)

fclean: clean
	@rm -fv $(NAME)

re: fclean all

.PHONY: all clean fclean re
