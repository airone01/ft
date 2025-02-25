/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:29:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 10:45:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*initialize_buffer(char *buffer)
{
	if (!buffer)
		buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	return (buffer);
}

char	*process_read(int fd, char *buffer, char *temp)
{
	char	*joined;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		joined = ft_strjoin(buffer, temp);
		if (!joined)
		{
			free(temp);
			return (NULL);
		}
		free(buffer);
		buffer = joined;
	}
	return (buffer);
}

char	*read_buffer(int fd, char *buffer)
{
	char	*temp;

	buffer = initialize_buffer(buffer);
	if (!buffer)
		return (NULL);
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	buffer = process_read(fd, buffer, temp);
	free(temp);
	return (buffer);
}
