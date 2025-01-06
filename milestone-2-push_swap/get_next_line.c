/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:04:17 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/06 20:58:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @brief	Main function flow and loop to read from the file descriptor
 * @param	fd The file descriptor to read from
 * @param	line The current line being read
 * @returns The index of the newline character in the line
 */
ssize_t	read_until_nl(int fd, char **line)
{
	static uint8_t	buff[1024];
	ssize_t			bytes_read;
	char			*tmp;

	while (!ft_strchr(*line, '\n'))
	{
		bytes_read = read(fd, buff, 1024);
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
	static uint8_t	remain[1024];
	ssize_t			index;
	char			*line;

	if (fd < 0)
		return (NULL);
	if (remain[0])
		line = ft_strdup((const char *)remain);
	else
		line = NULL;
	index = 0;
	while (index < 1024)
		remain[index++] = 0;
	index = read_until_nl(fd, &line);
	if (index < 0)
		return (NULL);
	if (index == 1)
		return (line);
	ft_strlcpy((char *)remain, (char *)line + index + 1, 1024);
	line[index + 1] = '\0';
	return (line);
}
