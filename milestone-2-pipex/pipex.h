/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 18:30:07 by elagouch         ###   ########.fr       */
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

// Error management
void	perror_errno_and_exit(size_t err);
void	perror_and_exit(void);

// Argument management
void	args_valid(size_t argc, char **argv, ssize_t *fds);

// Files IO
char	*file_read(ssize_t fd);
void	file_write(ssize_t fd, char *file);

// Environment variables
char	*env_find(char **envp, char *var);
char	*env_find_bin(char **envp, char *bin);

// Misc
char	*path_find_bin(char *path, char *bin);
char	*find_bin(char **envp, char *bin);

#endif
