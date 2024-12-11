/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 18:43:22 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The  memchr()  function scans the initial n bytes of the memory area pointed
 * to by s for the first instance of c.  Both c and the  bytes  of  the  memory
 * area pointed to by s are interpreted as uint8_t.
 * @param	s	Haystack
 * @param	c	Needle
 * @param	n	Max bytes to scan`
 * @returns	pointer to the matching byte or NULL if the character does not occur
 * in the given memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	uint8_t	*se;

	se = (uint8_t *)s;
	while (n--)
	{
		if (*se == (uint8_t)c)
			return (se);
		se++;
	}
	return (0);
}
