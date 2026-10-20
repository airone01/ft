ifndef VERBOSE
MAKEFLAGS += --silent
.SILENT:
endif

NAME := libb.a
B := ../B

SRC := char close getchar lchar open putchar read write
SRC := $(addsuffix .b, $(SRC))
ASM := $(SRC:.b=.s)
OBJ := $(SRC:.b=.o)

AR := ar
ARFLAGS := rcs

AS := as
ASFLAGS := --32

REDHB := \e[1;102;30m
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
	@printf "$(BLUHB) CC $(CRESET) $<\n"
	@$(B) < $< > $@

clean:
	@rm -fv $(OBJ) $(ASM)

fclean:
	@rm -fv $(NAME)

re: fclean all

.PHONY: all clean fclean re
