/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:23:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_putstr_fd
/**
 * Outputs the string ’s’ to the given file descriptor.
 * @param	s	The string to output
 * @param	fd	The file descriptor on which to write
 */
void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s) * sizeof(char));
}
// GPM? end ft_putstr_fd
