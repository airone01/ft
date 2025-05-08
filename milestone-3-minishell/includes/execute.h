/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:43:21 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:39:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

// *************************************************************************** #
//                                 Structures                                  #
// *************************************************************************** #

typedef struct s_pipeline_init
{
	t_command	*current;
	int			prev_pipe_read;
	int			i;
	int			cmd_count;
}				t_pipeline_init;

typedef struct s_pipeline
{
	pid_t		*pids;
	int			prev_pipe_read;
	int			i;
}				t_pipeline;

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// execute_commands.c
void			execute_commands(t_ctx *ctx, t_command *cmd);

// execute_builtin.c
int				execute_builtin(t_ctx *ctx, t_command *cmd);
bool			is_builtin_command(char *cmd_name);

// execute_pipeline.c
void			execute_pipeline(t_ctx *ctx, t_command *cmd);

// heredoc.c
int				read_all_heredocs(t_ctx *ctx);

// heredoc_expand.c
char			*expand_variables_in_line(t_ctx *ctx, char *line);

// heredoc_expand_utils.c
char			*init_expansion(char *line);
char			*extract_var_name(char *str, int start, int end);

// heredoc_process.c
int				read_heredoc_content(int *pipe_fds, char *delimiter,
					t_ctx *ctx);

// heredoc_signals
void			reset_heredoc_state(void);
bool			is_heredoc_interrupted(void);
int				interrupt_check_hook(void);

// heredoc_utils.c
char			*replace_substring(char *str, int start, int end,
					char *replacement);

// heredoc_utils2.c
int				read_heredoc_line(char *delimiter, char **line);

// redir_cleanup.c
void			cleanup_heredoc_resources(t_ctx *ctx);

// redirection.c
bool			apply_redirections(t_command *cmd);
bool			save_original_fds(int *stdin_fd, int *stdout_fd);
void			restore_original_fds(int stdin_fd, int stdout_fd);

// redirection_input.c
bool			apply_input_redirection(t_command *cmd);

// redirection_output.c
bool			apply_output_redirection(t_command *cmd);

// execute_pipeline_utils.c
int				count_commands(t_command *cmd);
void			cleanup_pipes(int prev_pipe_read, int pipe_fds[2],
					int has_next);
void			wait_for_children(t_ctx *ctx, pid_t *pids, int cmd_count);
bool			create_pipe(int pipe_fds[2]);
void			execute_builtin_and_exit(t_ctx *ctx, t_command *cmd, int *pids);
bool			setup_pipeline_step(t_command *current, int pipe_fds[2],
					pid_t *pids);

// execute_pipeline_child.c
void			execute_command_in_child(t_ctx *ctx, t_command *cmd, t_fds fds,
					int *pids);

#endif
