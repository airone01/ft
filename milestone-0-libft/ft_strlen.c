/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 12:01:45 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strlen
/**
 * Gets the length of a string.
 * Optimized implementation using magic numbers and word-aligned reads.
 *
 * @param	str	String to get length from
 *
 * @returns		Length of str
 */
unsigned long	ft_strlen(const char *str)
{
	const unsigned long	*long_ptr;
	unsigned long		word;
	const char			*char_ptr = str;

	while (((unsigned long)char_ptr & (sizeof(long) - 1)) != 0)
	{
		if (!*char_ptr)
			return ((unsigned long)(char_ptr - str));
		char_ptr++;
	}
	long_ptr = (const unsigned long *)char_ptr;
	while (1)
	{
		word = *long_ptr;
		if (((word - 0x0101010101010101) & ~word & 0x8080808080808080))
			break ;
		long_ptr++;
	}
	char_ptr = (const char *)long_ptr;
	while (*char_ptr)
		char_ptr++;
	return ((unsigned long)(char_ptr - str));
}
// GPM? end ft_strlen
