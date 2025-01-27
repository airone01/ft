/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:09:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/27 19:26:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
void	perror_errno_and_exit(int err);
void	perror_and_exit(void);

// Argument management
void	args_valid(int argc, char **argv, int *fds);

// Files IO
char	*file_read(int fd);
void	file_write(int fd, char *file);

#endif
