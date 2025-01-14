/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:27:23 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:24:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

// GPM? begin ft_strcmp
/**
 * The strcmp() function compares the two strings s1 and s2.  The locale is not
 * taken into account (for a locale-aware  comparison,  see  strcoll(3)).   The
 * comparison is done using unsigned characters.
 * strcmp() returns an integer indicating the result of the comparison, as fol‐
 * lows:
 * * 0, if the s1 and s2 are equal;
 * * a negative value if s1 is less than s2;
 * * a positive value if s1 is greater than s2.
 * @param	s1	First string
 * @param	s2	Second string
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, ULLONG_MAX));
}
// GPM? end ft_strcmp
