/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:29:29 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/10 19:42:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef FD_SIZE
#  define FD_SIZE 1024
# endif

# include "../milestone-0-libft/libft.h"                 // GPM!

# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

#endif
