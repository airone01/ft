/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 11:55:52 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strchr
/**
 * The strchr() function returns a pointer to the first occurrence of the char‐
 * acter c in the string s.
 * @param	s	Haystack
 * @param	c	Needle
 * @returns     Pointer to the matched character or NULL if the character is
 * not found.
 */
char	*ft_strchr(const char *s, char c)
{
	while (*s != (char)c)
		if (!*s++)
			return (NULL);
	return ((char *)s);
}
// GPM? end ft_strchr
