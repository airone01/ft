/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 16:16:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef PIPEX_PIPES
#  define PIPEX_PIPES
#  define PIPEX_PIPES_MIN 2
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
# include <unistd.h>

// Global data ("app")
typedef struct s_app
{
	int		fd_file_in;
	int		fd_file_out;
	// t_list of file[2]
	t_list	*fd_pipes;
	// t_list of char
	t_list	*cmds;
	// t_list of char*
	t_list	*cmdas;
}			t_app;

// "app" commands
void		app_exit_errno(t_app app, size_t errno_p);
void		app_exit(t_app app);
t_app		app_new(void);

// Memory management
void		free_strings(char **strings);
void		app_free(t_app app);
void		free_fds(t_app app);
void		nothing(void *ptr);

// File descriptors and pipes
void		args_valid(t_app *app, size_t argc, char **argv);
void		fds_open(t_app *app);

// Environment variables
char		*env_find(char **envp, char *var);
char		*env_find_bin(t_app *app, char **envp, char *bin);

// Simple commands
void		populate_cmds(t_app *app, int argc, char **argv, char **envp);
void		cmds_to_cmdas(t_app *app, char **envp);
void		cmda_print(void *content);
void		cmd_print(void *content);
void		cmda_free(void *cmda);
void		cmd_free(void *cmd);

// Path resolution
char		*path_find_bin(t_app *app, char *path, char *bin);
char		*find_bin(t_app *app, char **envp, char *bin);

#endif
