/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 18:44:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The  memmove()  function  copies n bytes from memory area src to memory area
 * dest.  The memory areas may overlap: copying takes place as though the bytes
 * in  src are first copied into a temporary array that does not overlap src or
 * dest, and the bytes are then copied from the temporary array to dest.
 * @param	s	Pointer
 * @param	c	Constant byte
 * @param	n	Size in number of bytes
 * @returns     Pointer to the memory area s
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const uint8_t	*src2;
	uint8_t			*dest2;

	if (!dest && !src)
		return (dest);
	if (n == 0)
		return (dest);
	src2 = src;
	dest2 = dest;
	if ((dest2 > src2) && (dest2 < src2 + n))
	{
		dest2 += n;
		src2 += n;
		while (n--)
			*--dest2 = *--src2;
		return (dest);
	}
	return (ft_memcpy(dest, src, n));
}
