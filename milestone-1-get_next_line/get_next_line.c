/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:28:31 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/29 13:12:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

/**
 * @brief	Reads the next line from a file descriptor
 *
 * The function will work as expected both when reading a file and
 * when reading from the standard input.
 * The returned line should include the terminating `\n` character,
 * except if the end of file was reached and does not end with a `\n` character.
 *
 * @param	fd The file descriptor to read from
 *
 * @returns	The next line from the file descriptor or NULL if there is
 * 			nothing more to read or an error occurred
 */
char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	ssize_t		bytes_read;
	char		*line;
	char		*temp;
	char		read_buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	line = get_remaining_buffer(&buffer[fd]);
	if (line)
		return (line);
	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		read_buffer[bytes_read] = '\0';
		if (buffer[fd])
			temp = ft_strjoin(buffer[fd], read_buffer);
		else
			temp = ft_strdup(read_buffer);
		if (!temp)
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
			return (NULL);
		}
		free(buffer[fd]);
		buffer[fd] = temp;
		if (ft_strchr(buffer[fd], '\n'))
			return (get_remaining_buffer(&buffer[fd]));
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	}
	if (bytes_read >= 0 && buffer[fd] && *buffer[fd])
		return (get_remaining_buffer(&buffer[fd]));
	free(buffer[fd]);
	buffer[fd] = NULL;
	return (NULL);
}

/**
 * @brief	Returns the remaining buffer from a previous read
 * 			until the next newline character
 *
 * @param	buffer The buffer to read from
 *
 * @returns	The remaining buffer until the next newline character
 */
char	*get_remaining_buffer(char **buffer)
{
	char	*line;
	char	*newline_pos;
	char	*temp;

	if (!*buffer)
		return (NULL);
	newline_pos = ft_strchr(*buffer, '\n');
	if (newline_pos)
	{
		line = ft_substr(*buffer, 0, newline_pos - *buffer + 1);
		temp = ft_strdup(newline_pos + 1);
		free(*buffer);
		*buffer = temp;
		return (line);
	}
	else if (**buffer)
	{
		line = *buffer;
		*buffer = NULL;
		return (line);
	}
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*p;
	size_t			total;

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
