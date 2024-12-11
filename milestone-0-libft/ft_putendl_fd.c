/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 18:45:44 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Outputs the string ’s’ to the given file descriptor followed by a newline.
 * @param	s	The string to output
 * @param	fd	The file descriptor on which to write
 */
void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s) * sizeof(char));
	write(fd, "\n", sizeof(char));
}
