/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/05 22:48:43 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_memset
/**
 * The  memset() function fills the first n bytes of the memory area pointed to
 * by s with the constant byte c.
 * @param	s	Pointer
 * @param	c	Constant byte
 * @param	n	Size in number of bytes
 * @returns     Pointer to the memory area s
 */
void	*ft_memset(void *s, uint8_t c, size_t n)
{
	uint8_t	*pt;

	if (n != 0)
	{
		pt = s;
		while (n != 0)
		{
			*pt++ = (uint8_t)c;
			n--;
		}
	}
	return (s);
}
// GPM? end ft_memset
