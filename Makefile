# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 07:56:10 by elagouch          #+#    #+#              #
#    Updated: 2025/08/27 16:27:18 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               ANSI COLOR CODES                               #
# **************************************************************************** #

include $(realpath ./extra-make/art.mk)
COLOR	= $(COLOR_FT)

# **************************************************************************** #
#                                   METADATA                                   #
# **************************************************************************** #

GPM_FNAME	= ft

# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #

include $(realpath ./extra-make/commands.mk)

# **************************************************************************** #
#                                     JOBS                                     #
# **************************************************************************** #

# Format: milestone_number:job_name
JOBS	= 			\
	0:libft 		\
	1:born2beroot	\
	1:ft_printf		\
	1:get_next_line	\
	2:push_swap		\
	2:pipex			\
	2:fdf			\
	3:minishell		\
	3:philo			\
	4:cpp00			\
	4:cpp01			\
	4:cpp02			\
	4:cpp03			\
	4:cub3d
JOBS_EXTRA	=				\
	arthur					\
	ps-visualizer-minecraft

# **************************************************************************** #
#                                   MAPPING                                    #
# **************************************************************************** #

MILESTONE_TARGETS	= $(foreach job,$(JOBS),milestone$(word 1,$(subst :, ,$(job)))$(word 2,$(subst :, ,$(job))))
MILESTONE_EXTRAS	= $(foreach job,$(JOBS_EXTRA),extra-$(job))
SHORT_TARGETS		= $(foreach job,$(JOBS),$(word 2,$(subst :, ,$(job))))
ALL_TARGETS			= $(SHORT_TARGETS) $(MILESTONE_TARGETS)
# Get unique milestone numbers
MILESTONES = $(sort $(foreach job,$(JOBS),$(word 1,$(subst :, ,$(job)))))

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

default:
	@$(ECHO) "$(MSG)👀 Please choose a project to build or run 'make all'.\n"
	@$(ECHO) "$(MSG)👀 Run 'make list' to see all available projects.\n"

# List all projects organized by milestone
list:
	@$(ECHO) "$(MSG)👀 Available common core projects:$(RESET)\n"
	@$(foreach mile,$(MILESTONES),\
		$(foreach job,$(filter $(mile):%,$(JOBS)),\
			$(ECHO) "$(MSG) - $(mile) $(word 2,$(subst :, ,$(job)))\n"; \
		) \
	)
	@$(ECHO) "$(MSG)👀 Available extra projects:$(RESET)\n"
	@$(foreach job,$(JOBS_EXTRA),\
		$(ECHO) "$(MSG) - $(job)\n"; \
	)

# Generate the short-name targets (e.g., libft)
$(foreach job,$(JOBS),$(eval $(word 2,$(subst :, ,$(job))): milestone$(word 1,$(subst :, ,$(job)))$(word 2,$(subst :, ,$(job)))))

# Generate the milestone targets (e.g., milestone0libft)
define make_milestone_target
milestone$(word 1,$(subst :, ,$(1)))$(word 2,$(subst :, ,$(1))):
	@$(ECHO) "$(MSG)🏗️  Building $(word 2,$(subst :, ,$(1)))\n"
	@$(MAKE) -sC milestone-$(word 1,$(subst :, ,$(1)))-$(word 2,$(subst :, ,$(1)))
endef
define make_extra_target
extra-$(1):
	@$(ECHO) "$(MSG)🏗️  Building $(1)\n"
	@$(MAKE) -sC $(1)
endef

$(foreach job,$(JOBS),$(eval $(call make_milestone_target,$(job))))
$(foreach job,$(JOBS_EXTRA),$(eval $(call make_extra_target,$(job))))

title:
	@$(ECHO) "$(MSG)⢕⢕⢕⢕⢕⠅⢗⢕⠕⣠⠄⣗⢕⢕⠕⢕⢕⢕⠕⢠⣿⠐⢕⢕⢕⠑⢕⢕⠵⢕    __        _ __   ___\n"
	@$(ECHO) "$(MSG)⢕⢕⢕⢕⠁⢜⠕⢁⣴⣿⡇⢓⢕⢵⢐⢕⢕⠕⢁⣾⢿⣧⠑⢕⢕⠄⢑⢕⠅⢕   / /  __ __(_) /__/ (_)__  ___ _\n"
	@$(ECHO) "$(MSG)⢕⢕⠵⢁⠔⢁⣤⣤⣶⣶⣶⡐⣕⢽⠐⢕⠕⣡⣾⣶⣶⣶⣤⡁⢓⢕⠄⢑⢅⢑  / _ \\/ // / / / _  / / _ \\/ _ \`/\n"
	@$(ECHO) "$(MSG)⠍⣧⠄⣶⣾⣿⣿⣿⣿⣿⣿⣷⣔⢕⢄⢡⣾⣿⣿⣿⣿⣿⣿⣿⣦⡑⢕⢤⠱⢐ /_.__/\\_,_/_/_/\\_,_/_/_//_/\\_, /\n"
	@$(ECHO) "$(MSG)⢠⢕⠅⣾⣿⠋⢿⣿⣿⣿⠉⣿⣿⣷⣦⣶⣽⣿⣿⠈⣿⣿⣿⣿⠏⢹⣷⣷⡅⢐                           /___/\n"
	@$(ECHO) "$(MSG)⣔⢕⢥⢻⣿⡀⠈⠛⠛⠁⢠⣿⣿⣿⣿⣿⣿⣿⣿⡀⠈⠛⠛⠁⢀⣼⣿⣿⡇⢔    _____\n"
	@$(ECHO) "$(MSG)⢕⢕⢽⢸⢟⢟⢖⢖⢤⣶⡟⢻⣿⡿⠻⣿⣿⡟⢀⣿⣦⢤⢤⢔⢞⢿⢿⣿⠁⢕   / _/ /_\n"
	@$(ECHO) "$(MSG)⢕⢕⠅⣐⢕⢕⢕⢕⢕⣿⣿⡄⠛⢀⣦⠈⠛⢁⣼⣿⢗⢕⢕⢕⢕⢕⢕⡏⣘⢕  / _/ __/\n"
	@$(ECHO) "$(MSG)⢕⢕⠅⢓⣕⣕⣕⣕⣵⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣷⣕⢕⢕⢕⢕⡵⢀⢕⢕ /_/ \\__/\n"
	@$(ECHO) "$(MSG)⢑⢕⠃⡈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢃⢕⢕⢕\n"
	@$(ECHO) "$(MSG)🏗️  Building all projects\n"

all-core:
	@for job in $(JOBS); do \
		dir=milestone-$$(echo $$job | cut -d: -f1)-$$(echo $$job | cut -d: -f2); \
		(cd "$$dir" && $(MAKE)); \
	done
all-extra:
	@for job in $(JOBS_EXTRA); do \
		(cd "extra-$$job" && $(MAKE)); \
	done

all: title all-core all-extra
core: title all-core
common: core
commons: core
extra: title all-extra
extras: extra

# Clean targets with better path handling
clean:
	@$(ECHO) "$(MSG)🧹 Cleaning all projects\n"
	@for job in $(JOBS); do \
		dir=milestone-$$(echo $$job | cut -d: -f1)-$$(echo $$job | cut -d: -f2); \
		(cd "$$dir" && $(MAKE) clean); \
	done
	@for job in $(JOBS_EXTRA); do \
		(cd "extra-$$job" && $(MAKE) clean); \
	done

fclean:
	@$(ECHO) "$(MSG)🧹 Fcleaning all projects\n"
	@for job in $(JOBS); do \
		dir=milestone-$$(echo $$job | cut -d: -f1)-$$(echo $$job | cut -d: -f2); \
		(cd "$$dir" && $(MAKE) fclean); \
	done
	@for job in $(JOBS_EXTRA); do \
		(cd "extra-$$job" && $(MAKE) fclean); \
	done

# **************************************************************************** #
#                                MAKE METADATA                                 #
# **************************************************************************** #

MAKEFLAGS	+= --no-print-directory
.PHONY: clean fclean default $(ALL_TARGETS) all title all-core all-extra
