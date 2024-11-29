/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:29:20 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/29 13:13:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdint.h>

/*
I neeed:
- ft_substr
*/

/**
 * @brief	Get the length of a string
 *
 * @param	str The string to get the length of
 *
 * @returns	The length of the string
 *
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
 * @brief	Joins two strings together
 *
 * @param	s1 The first string
 * @param	s2 The second string
 *
 * @returns	A new string that is the result of joining s1 and s2
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*dst;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = (char *)ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!dst)
		return (0);
	ft_strlcpy(dst, s1, s1_len + 1);
	ft_strlcat(dst, s2, s1_len + s2_len + 1);
	return (dst);
}

/**
 * @brief	Duplicates a string.
 *
 * @param	s string to duplicate
 *
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
 * @brief	Allocates memory for an array of nmemb elements of size bytes each
 *
 * @param	nmemb Number of elements
 * @param	size Size of each element
 *
 * @returns	A pointer to the allocated memory
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

/**
 * @brief	Copies up to size - 1 characters from the string src to dst
 *
 * @param	dst The destination string
 * @param	src The source string
 * @param	size The size of the destination buffer
 *
 * @returns	The length of the string that was copied
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	s = &(s[start]);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (0);
	ft_strlcpy(dst, s, len + 1);
	return (dst);
}
