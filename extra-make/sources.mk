# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 16:05:45 by elagouch          #+#    #+#              #
#    Updated: 2025/05/12 13:25:05 by elagouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GPM? begin make_sources_mk
# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

_SRC_LIBFT_COMMON				:=	\
	ft_abs							\
	ft_atoi							\
	ft_atol							\
	ft_atoul						\
	ft_bzero						\
	ft_calloc						\
	ft_env_find						\
	ft_isalnum						\
	ft_isalpha						\
	ft_isascii						\
	ft_isdigit						\
	ft_isprint						\
	ft_isspace						\
	ft_itoa							\
	ft_lstadd_back_bonus			\
	ft_lstadd_front_bonus			\
	ft_lstat_bonus					\
	ft_lstclear_bonus				\
	ft_lstdelone_bonus				\
	ft_lstiter_bonus				\
	ft_lstlast_bonus				\
	ft_lstmap_bonus					\
	ft_lstnew_bonus					\
	ft_lstsize_bonus				\
	ft_max							\
	ft_memchr						\
	ft_memcmp						\
	ft_memcpy						\
	ft_memmove						\
	ft_memset						\
	ft_min							\
	ft_putchar_fd					\
	ft_putendl_fd					\
	ft_putnbr_fd					\
	ft_putstr_fd					\
	ft_realloc						\
	ft_recalloc						\
	ft_split						\
	ft_strchr						\
	ft_strcmp						\
	ft_strdup						\
	ft_striteri						\
	ft_strjoin						\
	ft_strlcat						\
	ft_strlcpy						\
	ft_strlen						\
	ft_strmapi						\
	ft_strncmp						\
	ft_strnstr						\
	ft_strrchr						\
	ft_strtol						\
	ft_strtoul						\
	ft_strtrim						\
	ft_substr						\
	ft_tolower						\
	ft_toupper
_SRC_LIBFT_COMMON				:=	\
	$(addprefix src/, $(_SRC_LIBFT_COMMON))
_SRC_LIBFT_MANDATORY			:=	\
	$(_SRC_LIBFT_COMMON)
_SRC_LIBFT_BONUS				:=	\
	$(_SRC_LIBFT_COMMON)

_SRC_FT_PRINTF_COMMON			:=	\
	ft_printf						\
	ft_putchar						\
	ft_putnbr_base_ssize			\
	ft_putstr_ssize
_SRC_FT_PRINTF_COMMON			:=	\
	$(addprefix src/, $(_SRC_FT_PRINTF_COMMON))
_SRC_FT_PRINTF_MANDATORY		:=	\
	$(_SRC_FT_PRINTF_COMMON)
_SRC_FT_PRINTF_BONUS			:=	\
	$(_SRC_FT_PRINTF_COMMON)

_SRC_GNL_COMMON					:=	\
	get_next_line					\
	get_next_line_utils				\
	files_utils						\
	files_utils2
_SRC_GNL_COMMON					:=	\
	$(addprefix src/, $(_SRC_GNL_COMMON))
_SRC_GNL_MANDATORY				:=	\
	$(_SRC_GNL_COMMON)
_SRC_GNL_BONUS					:=	\
	$(_SRC_GNL_COMMON)

_SRC_PUSH_SWAP_COMMOM			:=	\
	args_legit						\
	mani_swap						\
	mani_push						\
	mani_rotate						\
	mani_rrotate					\
	parse_stdin						\
	sort_cheapest					\
	sort_cost						\
	sort_large						\
	sort_move						\
	sort_push_save_three			\
	sort_shift_back					\
	sort_tiny						\
	stack_add_back					\
	stack_clear						\
	stack_clear_error				\
	stack_dupes						\
	stack_indexes					\
	stack_iter						\
	stack_last						\
	stack_legit						\
	stack_lowest_pos				\
	stack_max						\
	stack_new						\
	stack_pos						\
	stack_size						\
	stack_sorted					\
	std_error
_SRC_PUSH_SWAP_MANDATORY		:=	\
	_main							\
	$(_SRC_PUSH_SWAP_COMMOM)
_SRC_PUSH_SWAP_MANDATORY		:=	\
	$(addprefix src/, $(_SRC_PUSH_SWAP_MANDATORY))
_SRC_PUSH_SWAP_BONUS			:=	\
	checker							\
	checker_utils					\
	$(_SRC_PUSH_SWAP_COMMOM)
_SRC_PUSH_SWAP_BONUS			:=	\
	$(addprefix src/, $(_SRC_PUSH_SWAP_BONUS))

_SRC_PIPEX_COMMON				:=	\
	app_exit						\
	app_free						\
	app_free_utils					\
	app_new							\
	args_cmdas						\
	cmda_args						\
	cmda_free						\
	cmda_print						\
	env_find						\
	env_find_bin					\
	exec_cmdas						\
	exec_cmdas_get_fds				\
	exec_cmda_child					\
	find_bin						\
	bonus_here_doc					\
	path_find_bin
_SRC_PIPEX_MANDATORY			:=	\
	_main							\
	args_valid						\
	$(_SRC_PIPEX_COMMON)
_SRC_PIPEX_BONUS				:=	\
	_main_bonus						\
	args_valid_bonus				\
	$(_SRC_PIPEX_COMMON)

_SRC_FDF_COMMON					:=	\
	_main							\
	args_check						\
	clear_utils						\
	color_get						\
	color_get_by_scheme				\
	color_get_line					\
	color_parsing					\
	color_utils						\
	ctx_clear						\
	ctx_init						\
	debug_toggle					\
	error							\
	error_arg						\
	error_file						\
	error_map						\
	error_math						\
	error_memory					\
	error_mlx						\
	fast_atoi						\
	file_open						\
	free_2d_array					\
	fuzzy_equals					\
	initial_scale					\
	malloc							\
	map_elevation					\
	map_parse						\
	map_parse_utils					\
	map_utils						\
	mlx_bresenham					\
	mlx_bresenham_utils				\
	mlx_hooks						\
	mlx_hooks_key					\
	mlx_pixel_put					\
	mlx_render_line					\
	mlx_render_lod					\
	mlx_render_lod_debug			\
	mlx_render_lod_debug_utils		\
	mlx_render_next_frame			\
	mlx_render_section				\
	mlx_render_section_debug		\
	mlx_render_section_utils		\
	mlx_render_viewport				\
	point3d_rotate					\
	point_add						\
	point_cabinet_project			\
	point_conic_project				\
	point_distance					\
	point_dot						\
	point_iso_project				\
	point_lerp						\
	point_magnitude					\
	point_normalize					\
	point_rotate					\
	point_scale						\
	point_sub
_SRC_FDF_COMMON					:=	\
	$(addprefix src/, $(_SRC_FDF_COMMON))
_SRC_FDF_MANDATORY				:=	\
	$(_SRC_FDF_COMMON)
_SRC_FDF_BONUS					:=	\
	$(_SRC_FDF_COMMON)

_SRC_MINISHELL_COMMON			:=	\
	_main							\
	bin_find						\
	bin_find_path					\
	bin_find_utils					\
	builtin_cd						\
	builtin_cd_utils				\
	builtin_echo					\
	builtin_env						\
	builtin_exit					\
	builtin_export					\
	builtin_export_utils			\
	builtin_export_utils2			\
	builtin_pwd						\
	builtin_unset					\
	cleanup_utils					\
	command_add						\
	command_new						\
	command_parse					\
	command_parse_utils				\
	command_parse_utils2			\
	ctx_error_exit					\
	env								\
	env_find						\
	env_find_bin					\
	env_quotes						\
	env_quotes_utils				\
	env_utils						\
	error							\
	error_utils						\
	error_utils2					\
	execute_builtin					\
	execute_commands				\
	execute_pipeline				\
	execute_pipeline_child			\
	execute_pipeline_utils			\
	free_2d_array					\
	free_command					\
	free_ctx						\
	free_env						\
	globals							\
	heredoc							\
	heredoc_expand					\
	heredoc_expand_utils			\
	heredoc_process					\
	heredoc_signals					\
	heredoc_utils					\
	heredoc_utils2					\
	init_ctx						\
	init_parse						\
	lexer_read						\
	lexer_read_utils				\
	lexer_read_utils2				\
	lexer_token						\
	lexer_token_is					\
	lexer_tokenize					\
	lexer_token_utils				\
	lexer_utils						\
	memory							\
	path_error						\
	redir_cleanup					\
	redirection						\
	redirection_input				\
	redirection_output				\
	signals							\
	token_checker					\
	token_checker_utils				\
	validation
_SRC_MINISHELL_COMMON			:=	\
	$(addprefix src/, $(_SRC_MINISHELL_COMMON))
_SRC_MINISHELL_MANDATORY		:=	\
	$(_SRC_MINISHELL_COMMON)
_SRC_MINISHELL_BONUS			:=	\
	$(_SRC_MINISHELL_COMMON)
_SRC_PHILO_COMMON				:=	\
	_main							\
	args							\
	death_check						\
	free_ctx						\
	ft_atoul						\
	ft_calloc						\
	ft_isdigit						\
	ft_isspace						\
	ft_itoa							\
	ft_memset						\
	ft_strcmp						\
	ft_strlen						\
	ft_strncmp						\
	ft_usleep						\
	init_ctx						\
	init_mutexes					\
	init_philos						\
	is_it_over						\
	launch_big_brother				\
	launch_philos					\
	log_action						\
	philo_utils						\
	routine
_SRC_PHILO_COMMON				:=	\
	$(addprefix src/, $(_SRC_PHILO_COMMON))
_SRC_PHILO_MANDATORY			:=	\
	$(_SRC_PHILO_COMMON)
_SRC_PHILO_BONUS				:=	\
	$(_SRC_PHILO_COMMON)
# GPM? end make_sources_mk
