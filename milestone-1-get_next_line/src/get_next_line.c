/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:28:31 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 13:23:59 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *buffer)
{
	int		i;
	char	*line;

	if (!buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (unsigned long)(i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*get_new_buffer(char *buffer, int i)
{
	char	*new_buffer;
	int		j;

	new_buffer = malloc(sizeof(char) * (ft_strlen(buffer) - (unsigned long)i
				+ 1));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

static char	*update_buffer(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	return (get_new_buffer(buffer, i));
}

/**
 * Reads the next line from a file descriptor and returns it as a
 * string. If the read buff has a line, it will return that line and
 * keep the rest of the buff for the next call. If the buff is
 * empty, it will read more data from the file descriptor.
 *
 * @param fd The file descriptor to read from
 * @returns The next line from the file descriptor or NULL if there is
 * nothing more to read or an error occurred
 */
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = update_buffer(buffer);
	if (!buffer && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
