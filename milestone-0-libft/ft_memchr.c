/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/05 22:49:23 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_memchr
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
void	*ft_memchr(const void *s, uint8_t c, size_t n)
{
	uint8_t	*se;

	if (!s)
		return (NULL);
	se = (uint8_t *)s;
	while (n--)
	{
		if (*se == (uint8_t)c)
			return (se);
		se++;
	}
	return (0);
}
// GPM? end ft_memchr
