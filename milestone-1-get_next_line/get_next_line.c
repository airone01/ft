/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:28:31 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/05 01:24:43 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief	Reads the next line from a file descriptor and returns it as a
 * 			string. If the read buffer has a line, it will return that line and
 * 			keep the rest of the buffer for the next call. If the buffer is
 * 			empty, it will read more data from the file descriptor.
 * @param	fd The file descriptor to read from
 * @returns	The next line from the file descriptor or NULL if there is
 * 			nothing more to read or an error occurred
 */
char	*get_next_line(int fd)
{
	static uint8_t	remain[BUFFER_SIZE];
	ssize_t			index;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (remain[0])
		line = ft_strdup((const char *)remain);
	else
		line = NULL;
	index = 0;
	while (index < BUFFER_SIZE)
		remain[index++] = 0;
	index = read_until_nl(fd, &line);
	if (index < 0)
		return (NULL);
	if (index == 1)
		return (line);
	ft_strlcpy((char *)remain, (char *)line + index + 1, BUFFER_SIZE);
	line[index + 1] = '\0';
	return (line);
}

/**
 * @brief	Main function flow and loop to read from the file descriptor
 * @param	fd The file descriptor to read from
 * @param	line The current line being read
 * @returns The index of the newline character in the line
 */
ssize_t	read_until_nl(int fd, char **line)
{
	static uint8_t	buff[BUFFER_SIZE];
	ssize_t			bytes_read;
	char			*tmp;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(*line, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (-1);
		if (bytes_read == 0)
			return (1);
		buff[bytes_read] = '\0';
		tmp = ft_strjoin(*line, (char *)buff);
		free(*line);
		if (!tmp)
			return (free(line), -1);
		*line = tmp;
	}
	return (ft_strchr(*line, '\n') - *line);
}

/**
 * @brief	Returns the length of a string
 * @param	str The string to measure
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
 * @brief	Concatenates two strings
 * @param	dst The destination string
 * @param	str The string to measure
 * @param	size The maximum number of characters to measure
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
 * The calloc() function allocates memory for an array  of  nmemb  elements  of
 * size  bytes  each and returns a pointer to the allocated memory.  The memory
 * is set to zero.  If nmemb or size is 0, then calloc() returns  either  NULL,
 * or  a  unique pointer value that can later be successfully passed to free().
 * If the multiplication of nmemb and size would result  in  integer  overflow,
 * then  calloc() returns an error.  By contrast, an integer overflow would not
 * be detected in the following call to malloc(), with the result that  an  in‐
 * correctly sized block of memory would be allocated:
 * ```c
 * malloc(nmemb * size);
 * ```
 * @param	nmemb	Length of the variable
 * @param	size	Length of the type of the variable
 * @returns			Pointer to NUL-filled memory
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
