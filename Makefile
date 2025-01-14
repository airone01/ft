# ------------- ANSI -------------
TITLE		= \033[48;5;99;30;1m
RESET		= \033[0m
GREEN		= \033[1;32m
MSG			= $(TITLE) ft \t\t$(RESET)
SUCCESS		= $(MSG) $(GREEN)✅ Successfully built! 🚀$(RESET)\n
SUCCESSB	= $(MSG) $(GREEN)✅ Successfully built bonuses! 🚀$(RESET)\n
RESET		= \033[0m

# ----------- Commands -----------
ECHO	= printf
CD		= cd

# ------------ Jobs --------------
# Format: milestone_number:job_name
JOBS	= 			\
	0:libft 		\
	1:ft_printf		\
	1:get_next_line	\
	2:push_swap

# ------------ Mapping -----------
MILESTONE_TARGETS	= $(foreach job,$(JOBS),milestone$(word 1,$(subst :, ,$(job)))$(word 2,$(subst :, ,$(job))))
SHORT_TARGETS		= $(foreach job,$(JOBS),$(word 2,$(subst :, ,$(job))))
ALL_TARGETS			= $(SHORT_TARGETS) $(MILESTONE_TARGETS)

# Get unique milestone numbers
MILESTONES = $(sort $(foreach job,$(JOBS),$(word 1,$(subst :, ,$(job)))))

# ------------ Targets -----------
default:
	@$(ECHO) "$(MSG) 👀 Please choose a project to build or run 'make all'.\n"
	@$(ECHO) "\t\t    Run 'make list' to see all available projects.\n"

# List all projects organized by milestone
list:
	@$(ECHO) "$(MSG) 👀 Available Projects:$(RESET)\n"
	@$(foreach mile,$(MILESTONES),\
		$(foreach job,$(filter $(mile):%,$(JOBS)),\
			$(ECHO) "$(TITLE) $(mile) $(RESET)\t\t - $(word 2,$(subst :, ,$(job)))\n"; \
		) \
	)

# Generate the short-name targets (e.g., libft)
$(foreach job,$(JOBS),$(eval $(word 2,$(subst :, ,$(job))): milestone$(word 1,$(subst :, ,$(job)))$(word 2,$(subst :, ,$(job)))))

# Generate the milestone targets (e.g., milestone0libft)
define make_milestone_target
milestone$(word 1,$(subst :, ,$(1)))$(word 2,$(subst :, ,$(1))):
	@$(ECHO) "$(MSG) 🏗️  Building $(word 2,$(subst :, ,$(1)))\n"
	@$(CD) milestone-$(word 1,$(subst :, ,$(1)))-$(word 2,$(subst :, ,$(1))) && $(MAKE) -f *Makefile
endef

$(foreach job,$(JOBS),$(eval $(call make_milestone_target,$(job))))

all:
	@$(ECHO) "$(MSG) 🏗️  Building all projects\n"
	@for job in $(JOBS); do \
		dir=milestone-$$(echo $$job | cut -d: -f1)-$$(echo $$job | cut -d: -f2); \
		(cd "$$dir" && $(MAKE) -f *Makefile); \
	done

# Clean targets with better path handling
clean:
	@$(ECHO) "$(MSG) 🧹 Cleaning all projects\n"
	@for job in $(JOBS); do \
		dir=milestone-$$(echo $$job | cut -d: -f1)-$$(echo $$job | cut -d: -f2); \
		(cd "$$dir" && $(MAKE) -f *Makefile clean); \
	done

fclean:
	@$(ECHO) "$(MSG) 🧹 Fcleaning all projects\n"
	@for job in $(JOBS); do \
		dir=milestone-$$(echo $$job | cut -d: -f1)-$$(echo $$job | cut -d: -f2); \
		(cd "$$dir" && $(MAKE) -f *Makefile fclean); \
	done

#all: $(MILESTONE_TARGETS)

# ----------- Make meta ----------
MAKEFLAGS	+= --no-print-directory
.PHONY: clean fclean default $(ALL_TARGETS) all
