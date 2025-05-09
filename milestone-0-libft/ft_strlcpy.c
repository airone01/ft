/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 11:53:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strlcpy
/**
 * The strlcpy() and strlcat() functions copy and concatenate strings respec‐
 * tively.  They are designed to be safer, more consistent, and less error prone
 * replacements for strncpy(3) and strncat(3).  Unlike those functions,
 * strlcpy() and strlcat() take the full size of the buffer (not just the
 * length) and guarantee to NUL-terminate the result (as long as size is larger
 * than 0 or, in the case of strlcat(), as long as there is at least one byte
 * free in dst). Note that a byte for the NUL should be included in size. Also
 * note that strlcpy() and strlcat() only operate on true “C” strings. This
 * eans that for strlcpy() src must be NUL-terminated and for strlcat() both
 * src and dst must be NUL-terminated.
 * The strlcpy() function copies up to size - 1 characters from the NUL-termi‐
 * nated string src to dst, NUL-terminating the result.
 * @param	dest	Destination pointer
 * @param	src		Source pointer
 * @param	size	Number of characters to copy
 * @returns         Total length of the string the function tried to create
 */
unsigned long	ft_strlcpy(char *dst, const char *src, unsigned long size)
{
	const char	*src_start = src;

	if (size > 0)
	{
		while (--size > 0 && *src)
		{
			*dst++ = *src++;
		}
		*dst = '\0';
	}
	while (*src)
		src++;
	return ((unsigned long)(src - src_start));
}
// GPM? end ft_strlcpy
