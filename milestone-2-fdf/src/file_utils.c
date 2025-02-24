/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:45:49 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 11:36:42 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*append_line(char *content, char *line, size_t *total_len)
{
	char	*tmp;

	tmp = content;
	content = malloc(*total_len + strlen(line) + 1);
	if (!content)
	{
		free(line);
		free(tmp);
		return (NULL);
	}
	if (tmp)
	{
		memcpy(content, tmp, *total_len);
		free(tmp);
	}
	memcpy(content + *total_len, line, strlen(line));
	*total_len += strlen(line);
	content[*total_len] = '\0';
	free(line);
	return (content);
}

static int	get_line_width(char *line)
{
	int	width;
	int	i;

	width = 0;
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (ft_isdigit(line[i]) || line[i] == '-')
		{
			width++;
			while (line[i] && !ft_isspace(line[i]) && line[i] != '\n')
				i++;
		}
		while (line[i] && ft_isspace(line[i]) && line[i] != '\n')
			i++;
	}
	return (width);
}

/**
 * @brief	Reads the entire content of a file using get_next_line.
 *
 * @param	fd			The file descriptor.
 * @param	line_width	The width of the first line to set.
 *
 * @returns	The content of the file.
 */
char	*read_entire_file(int fd, unsigned long *line_width)
{
	char	*content;
	char	*line;
	size_t	total_len;

	if (fd < 0 || !line_width)
		return (NULL);
	content = NULL;
	total_len = 0;
	*line_width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!*line_width)
			*line_width = (unsigned long)get_line_width(line);
		content = append_line(content, line, &total_len);
		if (!content)
			return (NULL);
		line = get_next_line(fd);
	}
	return (content);
}
