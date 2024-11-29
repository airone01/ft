/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:29:20 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/29 19:57:33 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
 * @brief	Locates the first occurrence of c in the string s
 * 			or returns NULL if c is not found
 *
 * @param	s The string to search
 * @param	c The character to search for
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

/**
 * @brief	Returns the remaining buffer from the first newline character
 *
 * @param	buffer The buffer to search
 *
 * @returns	The remaining buffer from the first newline character
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	uint8_t	*p;
	size_t	total;
	void	*ptr;

	if (size && nmemb > __SIZE_MAX__ / size)
		return (0);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (0);
	p = ptr;
	total = size * nmemb;
	while (total--)
		*p++ = 0;
	return (ptr);
}

/**
 * @brief	Returns the length of a string
 *
 * @param	str The string to measure
 *
 * @returns	The length of the string
 */
unsigned int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	if (size == 0)
		return (i);
	size--;
	while (size-- && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (i);
}

/**
 * @brief	Concats two strings
 *
 * @param	dst The destination string
 * @param	str The string to measure
 * @param	size The maximum number of characters to measure
 *
 * @returns	The length of the string
 */
unsigned int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	i = 0;
	while (size && src[i] && (dst_len + i) < (size - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/**
 * @brief	Fills a buffer with a constant byte
 *
 * @param	s The buffer to fill
 * @param	c The byte to fill the buffer with
 * @param	n The number of bytes to fill
 *
 * @returns	A pointer to the buffer
 */
void	ft_memset(void *s, int c, size_t n)
{
	uint8_t	*pt;

	if (n != 0)
	{
		pt = s;
		while (n != 0)
		{
			*pt++ = (uint8_t)c;
			n--;
		}
	}
}
