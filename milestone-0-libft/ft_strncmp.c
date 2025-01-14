/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:49 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:25:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strncmp
/**
 * The strcmp() function compares the two strings s1 and s2.  The locale is not
 * taken into account (for a locale-aware  comparison,  see  strcoll(3)).   The
 * comparison is done using unsigned characters.
 * strcmp() returns an integer indicating the result of the comparison, as fol‐
 * lows:
 * * 0, if the s1 and s2 are equal;
 * * a negative value if s1 is less than s2;
 * * a positive value if s1 is greater than s2.
 * The strncmp() function is similar, except it compares  only  the  first  (at
 * most) n bytes of s1 and s2.
 * @param	s1	First string
 * @param	s2	Second string
 * @param	n	Max bytes to compare
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
// GPM? end ft_strncmp
