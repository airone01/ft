/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:21:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_memcmp
/**
 * The  memcmp()  function  compares the first n bytes (each interpreted as un‐
 * signed char) of the memory areas s1 and s2.
 * @param	s1	First string
 * @param	s2	Second string
 * @param	n	Max bytes to compare
 * @returns     See below
 * The memcmp() function returns an integer less than,  equal  to,  or  greater
 * than  zero  if  the  first  n bytes of s1 is found, respectively, to be less
 * than, to match, or be greater than the first n bytes of s2.
 * For a nonzero return value, the sign is determined by the sign of  the  dif‐
 * ference  between the first pair of bytes (interpreted as uint8_t) that
 * differ in s1 and s2.
 * If n is zero, the return value is zero.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	uint8_t	*se1;
	uint8_t	*se2;
	size_t	i;

	if (n == 0)
		return (0);
	se1 = (uint8_t *)s1;
	se2 = (uint8_t *)s2;
	i = 0;
	while (n--)
	{
		if (se1[i] != se2[i])
			return ((uint8_t)se1[i] - (uint8_t)se2[i]);
		i++;
	}
	return (0);
}
// GPM? end ft_memcmp
