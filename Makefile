# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 12:51:33 by elagouch          #+#    #+#              #
#    Updated: 2024/11/29 09:26:29 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------- ANSI -------------
TITLE_PRI	= \033[48;5;99;37;1m
TITLE_SEC	= \033[48;5;78;30;1m
RESET		= \033[0m

# ----------- Commands -----------
ECHO	= echo
MAKE	= make
CD		= cd

# ------------ Jobs --------------
# Format: milestone_number:job_name
JOBS	= 			\
	0:libft 		\
	1:printf		\
	1:born2beroot	\
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
	@$(ECHO) "$(TITLE_PRI) ft \t\t$(RESET)Please choose a project to build."
	@$(ECHO) "\t\tRun 'make list' to see all available projects."

# List all projects organized by milestone
list:
	@$(ECHO) "$(TITLE_PRI) ft \t\t$(RESET)Available Projects:$(RESET)"
	@$(foreach mile,$(MILESTONES),\
		$(foreach job,$(filter $(mile):%,$(JOBS)),\
			echo "$(TITLE_SEC) $(mile) $(RESET)\t\t - $(word 2,$(subst :, ,$(job)))"; \
		) \
	)

# Generate the short-name targets (e.g., libft)
$(foreach job,$(JOBS),$(eval $(word 2,$(subst :, ,$(job))): milestone$(word 1,$(subst :, ,$(job)))$(word 2,$(subst :, ,$(job)))))

# Generate the milestone targets (e.g., milestone0libft)
define make_milestone_target
milestone$(word 1,$(subst :, ,$(1)))$(word 2,$(subst :, ,$(1))):
	@$(ECHO) "$(TITLE_PRI) ft \t\t$(RESET)Building $(word 2,$(subst :, ,$(1)))"
	@$(CD) milestone-$(word 1,$(subst :, ,$(1)))-$(word 2,$(subst :, ,$(1))) && $(MAKE)
endef

$(foreach job,$(JOBS),$(eval $(call make_milestone_target,$(job))))

# Clean targets with better path handling
clean:
	@$(ECHO) "$(TITLE_PRI) ft \t\t$(RESET)Cleaning all projects"
	@for job in $(JOBS); do \
		dir=milestone-$$(echo $$job | cut -d: -f1)-$$(echo $$job | cut -d: -f2); \
		if [ -d "$$dir" ]; then \
			(cd "$$dir" && $(MAKE) clean); \
		else \
			$(ECHO) "$(TITLE_SEC) $$(echo $$job | cut -d: -f1) $(RESET)\t\t - Directory $$dir not found"; \
		fi; \
	done

fclean:
	@$(ECHO) "$(TITLE_PRI) ft \t\t$(RESET)Fcleaning all projects"
	@for job in $(JOBS); do \
		dir=milestone-$$(echo $$job | cut -d: -f1)-$$(echo $$job | cut -d: -f2); \
		if [ -d "$$dir" ]; then \
			(cd "$$dir" && $(MAKE) fclean); \
		else \
			$(ECHO) "$(TITLE_SEC) $$(echo $$job | cut -d: -f1) $(RESET)\t\t - Directory $$dir not found"; \
		fi; \
	done

# ----------- Make meta ----------
MAKEFLAGS	+= --no-print-directory
.PHONY: clean fclean default $(ALL_TARGETS)