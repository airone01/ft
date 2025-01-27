/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:22:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_putchar_fd
/**
 * Outputs the character ’c’ to the given file descriptor.
 * @param	c	The character to output
 * @param	fd	The file descriptor on which to write
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}
// GPM? end ft_putchar_fd
