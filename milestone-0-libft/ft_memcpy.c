/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:22:00 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_memcpy
/**
 * The  memcpy()  function  copies  n bytes from memory area src to memory area
 * dest.  The memory areas must not overlap.  Use memmove(3) if the memory  ar‐
 * eas do overlap.
 * @param	dest	Destination pointer
 * @param	Src		Source pointer
 * @param	n		N-most bytes to copy
 * @returns			Pointer to the resulting memory area s
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const uint8_t	*src2;
	uint8_t			*dest2;

	if (!dest && !src)
		return (dest);
	if (n != 0)
	{
		src2 = (const uint8_t *)src;
		dest2 = (uint8_t *)dest;
		while (n-- > 0)
			*dest2++ = *src2++;
	}
	return (dest);
}
// GPM? end ft_memcpy
