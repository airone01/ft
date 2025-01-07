/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:52 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/07 14:16:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The strrchr() function returns a pointer to the last occurrence of the char‐
 * acter c in the string s.
 * @param	s	Haystack
 * @param	c	Needle
 * @returns     Pointer to the matched character or NULL if the character is
 * not found.
 */
char	*ft_strrchr(const char *s, int c)
{
	char	*se;

	if (!s)
		return (NULL);
	se = NULL;
	while (*s)
	{
		if (*s == (char)c)
			se = (char *)s;
		s++;
	}
	if (*s == (char)c)
		se = (char *)s;
	return (se);
}
