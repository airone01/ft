# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:05:45 by elagouch          #+#    #+#              #
#    Updated: 2025/01/30 19:32:32 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #
# GPM? begin make_src_libft
_SRC_LIBFT	=				\
	ft_atoi					\
	ft_abs					\
	ft_bzero				\
	ft_calloc				\
	ft_isalnum				\
	ft_isalpha				\
	ft_isascii				\
	ft_isdigit				\
	ft_isprint				\
	ft_itoa					\
	ft_lstat_bonus			\
	ft_lstadd_back_bonus	\
	ft_lstadd_front_bonus	\
	ft_lstclear_bonus		\
	ft_lstdelone_bonus		\
	ft_lstiter_bonus		\
	ft_lstlast_bonus		\
	ft_lstmap_bonus			\
	ft_lstnew_bonus			\
	ft_lstsize_bonus		\
	ft_memchr				\
	ft_memcmp				\
	ft_memcpy				\
	ft_memmove				\
	ft_memset				\
	ft_putchar_fd			\
	ft_putendl_fd			\
	ft_putnbr_fd			\
	ft_putstr_fd			\
	ft_split				\
	ft_strdup				\
	ft_strrchr				\
	ft_strchr				\
	ft_strcmp				\
	ft_striteri				\
	ft_strjoin				\
	ft_strlcat				\
	ft_strlcpy				\
	ft_strlen				\
	ft_strmapi				\
	ft_strnstr				\
	ft_strncmp				\
	ft_strtrim				\
	ft_tolower				\
	ft_toupper				\
	ft_substr
# GPM? end make_src_libft
_SRC_GNL_BONUS	=			\
	get_next_line			\
	get_next_line_utils
# GPM? begin make_src_push_swap
_SRC_PUSH_SWAP_COMMOM	=	\
	args_legit				\
	mani_swap				\
	mani_push				\
	mani_rotate				\
	mani_rrotate			\
	parse_stdin				\
	sort_cheapest			\
	sort_cost				\
	sort_large				\
	sort_move				\
	sort_push_save_three	\
	sort_shift_back			\
	sort_tiny				\
	stack_add_back			\
	stack_clear				\
	stack_clear_error		\
	stack_dupes				\
	stack_indexes			\
	stack_iter				\
	stack_last				\
	stack_legit				\
	stack_lowest_pos		\
	stack_max				\
	stack_new				\
	stack_pos				\
	stack_size				\
	stack_sorted			\
	std_error
_SRC_PUSH_SWAP	=			\
	push_swap				\
	$(_SRC_PUSH_SWAP_COMMOM)
_SRC_PUSH_SWAP_BONUS	=	\
	checker					\
	checker_utils			\
	$(_SRC_PUSH_SWAP_COMMOM)
# GPM? end make_src_push_swap
# GPM? begin make_src_ft_strlen
_SRC_FT_PRINTF		=		\
	ft_printf				\
	ft_putchar				\
	ft_putnbr_base_ssize	\
	ft_putstr_ssize
# GPM? end make_src_ft_strlen
# GPM? negin make_src_pipex
_SRC_PIPEX	=				\
	_main					\
	app_exit				\
	app_free				\
	app_free_utils			\
	app_new					\
	args_cmds				\
	args_valid				\
	cmd_free				\
	cmd_print				\
	cmd_to_cmda				\
	cmda_free				\
	cmda_print				\
	env_find				\
	env_find_bin			\
	exec_cmdas				\
	exec_cmdas_get_fds		\
	exec_cmda_child			\
	find_bin				\
	path_find_bin
# GPM? end make_src_pipex
