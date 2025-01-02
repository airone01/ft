/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:29:20 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/16 13:44:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Get the length of a string
 * @param	str The string to get the length of
 * @returns	The length of the string
 * @note	Implemented iteratively and not recursively to avoid stack overflow
 */
size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * Joins two strings together
 * @param	s1 The first string
 * @param	s2 The second string
 * @returns	A new string that is the result of joining s1 and s2
 * @note	The caller is responsible for freeing the memory
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*dst;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = (char *)ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, s1_len + 1);
	ft_strlcat(dst, s2, s1_len + s2_len + 1);
	return (dst);
}

/**
 * Duplicates a string.
 * @param	s string to duplicate
 * @returns	A pointer to the newly allocated string,
 * 			or NULL if the allocation failed
 */
char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dst;

	dst = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!dst)
		return (0);
	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	return ((char *)dst);
}

/**
 * Locates the first occurrence of c in the string s
 * or returns NULL if c is not found
 * @param	s The string to search
 * @param	c The character to search for
 * @returns	A pointer to the allocated memory
 */
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
