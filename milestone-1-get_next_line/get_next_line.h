/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:29:29 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 13:23:26 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# ifndef FD_SIZE
#  define FD_SIZE 1024
# endif

# ifndef RF_DEFINE
#  define RF_DEFINE
#  define RF_INITIAL_CAPACITY 128
#  define RF_GROWTH_FACTOR 2
# endif

# include "libft.h"
# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_file_content
{
	char		**lines;
	size_t		size;
	size_t		capacity;
}				t_file_content;

// Utils
t_file_content	*init_file_content(void);
char			*read_buffer(int fd, char *buffer);
int				append_line(t_file_content *content, char *line);
int				expand_capacity(t_file_content *content);

// GNL
char			**read_entire_file(int fd);
char			*get_next_line(int fd);

#endif
