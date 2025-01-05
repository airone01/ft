/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/05 01:32:45 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// GPM? begin ft_strchr
/**
 * The strchr() function returns a pointer to the first occurrence of the char‐
 * acter c in the string s.
 * @param	s	Haystack
 * @param	c	Needle
 * @returns     Pointer to the matched character or NULL if the character is
 * not found.
 */
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
// GPM? end ft_strchr
