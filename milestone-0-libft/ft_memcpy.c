/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 18:44:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The  memcpy()  function  copies  n bytes from memory area src to memory area
 * dest.  The memory areas must not overlap.  Use memmove(3) if the memory  ar‐
 * eas do overlap.
 * @param	s	Pointer
 * @param	c	Constant byte
 * @param	n	Size in number of bytes
 * @returns	pointer to the memory area s
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
