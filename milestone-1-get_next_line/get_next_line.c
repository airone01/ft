/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:28:31 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/09 13:06:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief	Reads the next line from a file descriptor and returns it as a
 * 			string. If the read buffer has a line, it will return that line and
 * 			keep the rest of the buffer for the next call. If the buffer is
 * 			empty, it will read more data from the file descriptor.
 *
 * @param	fd The file descriptor to read from
 *
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
    ft_memset(remain, 0, BUFFER_SIZE);
	index = read_until_nl(fd, &line);
	if (index < 0)
		return (free(line), NULL);
    if (index == 1)
        return (line);
    ft_strlcpy((char *) remain, (char *) line + index + 1, BUFFER_SIZE);
    line[index + 1] = '\0';
    return (line);
}

/**
 * @brief	Maiun function flow and loop to read from the file descriptor
 *
 * @param	fd The file descriptor to read from
 * @param	line The current line being read
 *
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
