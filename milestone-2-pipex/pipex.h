/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/31 16:13:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef PIPEX_PIPES
#  define PIPEX_PIPES
#  define PIPEX_PIPES_MIN 1
#  define PIPEX_PIPES_MAX 1024
# endif

# include "../milestone-0-libft/libft.h"                 // GPM!
# include "../milestone-1-ft_printf/ft_printf.h"         // GPM!
# include "../milestone-1-get_next_line/get_next_line.h" // GPM!
# include <errno.h>
# include <error.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// Global data
typedef struct s_app
{
	int		fd_file_in;
	int		fd_file_out;
	int		bonus_pipes[2];
	// t_list of char*
	t_list	*cmdas;
	char	**envp;
}			t_app;

// Global data functions
void		app_exit_errno(t_app app, size_t errno_p);
void		app_exit(t_app app);
t_app		app_new(char **envp);

// Memory management
void		free_strings(char **strings);
void		app_free(t_app app);
void		free_fds(t_app app);
void		nothing(void *ptr);

// Environment variables
char		*env_find(t_app app, char *var);
char		*env_find_bin(t_app *app, char *bin);

// Arguments parsing
char		**cmda_args(t_app *app, char *cmd);
void		populate_cmdas(t_app *app, int argc, char **argv);
void		cmda_print(void *content);
void		cmda_free(void *cmda);
int			args_valid(t_app *app, size_t argc, char **argv);

// Path resolution
char		*path_find_bin(t_app *app, char *path, char *bin);
char		*find_bin(t_app *app, char *bin);

// Execution
void		exec_cmdas(t_app app);
void		exec_cmda_child(t_app app, t_list *current_cmd, int *pipe_prev,
				int *pipe_curr);

// Execution: file descriptors
int			get_fd_in(t_app app, t_list *fd_pipes, int cmd_index);
int			get_fd_out(t_app app, t_list *fd_pipes, int cmd_index,
				int cmd_count);

// Bonus
int			handle_here_doc(t_app *app, char *limiter);

#endif
