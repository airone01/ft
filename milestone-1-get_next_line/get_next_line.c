/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:28:31 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/07 18:09:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Cleans the buff
 * @param	buff	Buffer
 */
void	ft_buff_clean(char *buff)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buff[i] != '\n' && buff[i] != 0)
		i++;
	if (buff[i] == '\n')
		i++;
	j = 0;
	while (buff[i + j])
	{
		buff[j] = buff[i + j];
		j++;
	}
	buff[j] = 0;
}

size_t	is_line(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	clear_static(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		buffer[i] = '\0';
		i++;
	}
}

/**
 * @brief	Reads the next line from a file descriptor and returns it as a
 * 			string. If the read buff has a line, it will return that line and
 * 			keep the rest of the buff for the next call. If the buff is
 * 			empty, it will read more data from the file descriptor.
 * @param	fd The file descriptor to read from
 * @returns	The next line from the file descriptor or NULL if there is
 * 			nothing more to read or an error occurred
 */
char	*get_next_line(int fd)
{
	static char	buffer[FD_SIZE][BUFFER_SIZE + 1];
	ssize_t		read_byte;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0 || FD_SIZE < 0)
		return (NULL);
	read_byte = 1;
	line = ft_strdup(buffer[fd]);
	if (!line)
		return (NULL);
	while (read_byte && is_line(line) == 0)
	{
		read_byte = read(fd, buffer[fd], BUFFER_SIZE);
		if (read_byte == -1)
			return (clear_static(buffer[fd]), free(line), NULL);
		buffer[fd][read_byte] = '\0';
		line = ft_strjoin(line, buffer[fd]);
		if (!line)
			return (NULL);
	}
	ft_buff_clean(buffer[fd]);
	if (line[0] == 0)
		return (free(line), NULL);
	return (line);
}
