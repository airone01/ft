/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:28:31 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 11:40:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Cleans the buff
 * @param	buff	Buffer
 */
void	ft_buff_clean(char *buff)
{
	long	i;
	long	j;

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

long	is_line(const char *str)
{
	long	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_free(char *left, char buffer[BUFFER_SIZE + 1], char *line,
		long bytes_read)
{
	char	*new;

	if (bytes_read == -1)
	{
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
		return (free(line), NULL);
	}
	buffer[bytes_read] = '\0';
	new = ft_strjoin(left, buffer);
	free(left);
	return (new);
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
	long		bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || FD_SIZE <= 0 || fd >= FD_SIZE)
		return (NULL);
	bytes_read = 1;
	line = ft_strdup(buffer[fd]);
	if (!line)
		return (free(line), NULL);
	while (bytes_read && is_line(line) == 0)
	{
		bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
		line = ft_strjoin_free(line, buffer[fd], line, bytes_read);
		if (!line)
			return (NULL);
	}
	ft_buff_clean(buffer[fd]);
	if (bytes_read == 0 && line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
