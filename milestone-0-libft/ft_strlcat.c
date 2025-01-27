/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:24:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strlcat
/**
 * The strlcpy() and strlcat() functions copy and concatenate strings respec‐
 * tively.  They are designed to be safer, more consistent, and less error prone
 * replacements for strncpy(3) and strncat(3).  Unlike those functions,
 * strlcpy() and strlcat() take the full size of the buffer (not just the
 * length) and guarantee to NUL-terminate the result (as long as size is larger
 * than 0 or, in the case of strlcat(), as long as there is at least one byte
 * free in dst). Note that a byte for the NUL should be included in size.
 * Also note that strlcpy() and strlcat() only operate on true “C” strings.
 * This means that for strlcpy() src must be NUL-terminated and for strlcat()
 * both src and dst must be NUL-terminated.
 * The strlcat() function appends the NUL-terminated string src to the end of
 * dst. It will append at most size - strlen(dst) - 1 bytes, NUL-terminating
 * the result.
 * @param	dst		Destination pointer
 * @param	src		Source pointer
 * @param	size	Number of characters to copy
 * @returns         Pointer to the destination string dst
 */
unsigned int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	i = 0;
	while (size && src[i] && (dst_len + i) < (size - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
// GPM? end ft_strlcat
