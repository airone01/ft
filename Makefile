# ------------- ANSI -------------
BG_BLURPLE	= \033[48;5;99m
RESET		= \033[0m

# ----------- Commands -----------
ECHO	= echo
MAKE	= make
CD		= cd

default:
	@echo "$(BG_BLURPLE) ft \t\t\t$(RESET)Please choose a project to build."

libft: milestone0libft
milestone0libft:
	@echo "$(BG_BLURPLE) ft \t\t\t$(RESET)Building libft"
	@$(CD) milestone-0-libft && $(MAKE)

clean:
	@echo "$(BG_BLURPLE) ft \t\t\t$(RESET)Cleaning all projects"
	@$(CD) milestone-0-libft && $(MAKE) clean

fclean:
	@echo "$(BG_BLURPLE) ft \t\t\t$(RESET)Fcleaning all projects"
	@$(CD) milestone-0-libft && $(MAKE) fclean

# ----------- Make meta ----------
MAKEFLAGS	+= --no-print-directory
.PHONY: clean fclean default \
	milestone0libft libft
