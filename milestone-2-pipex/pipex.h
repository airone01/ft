/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 16:48:44 by elagouch         ###   ########.fr       */
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
	ssize_t	fds[2];
	t_list	*cmds;
	char	*file1;
	char	*file2;
}			t_app;

// "app" commands
void		app_exit_errno(t_app app, size_t errno_p);
void		app_exit(t_app app);
void		app_free(t_app app);
t_app		app_new(void);

// Argument management
void		args_valid(t_app *app, size_t argc, char **argv);

// Files IO
char		*file_read(t_app *app, ssize_t fd);
void		file_write(t_app *app, ssize_t fd, char *file);

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

// Misc
char		*path_find_bin(t_app *app, char *path, char *bin);
char		*find_bin(t_app *app, char **envp, char *bin);
void		free_strings(char **strings);

#endif
