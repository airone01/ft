/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:45:49 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 13:09:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief	Reads the entire content of a file using get_next_line.
 *
 * @param	fd			The file descriptor.
 *
 * @returns	The content of the file.
 */

static void	cleanup_content(t_file_content *content)
{
	size_t	i;

	i = 0;
	while (i < content->size)
		free(content->lines[i++]);
	free(content->lines);
	free(content);
}

static int	process_line(t_file_content *content, char *line)
{
	if (!append_line(content, line))
	{
		cleanup_content(content);
		return (0);
	}
	return (1);
}

static char	**finalize_content(t_file_content *content)
{
	char	**result;

	if (content->size >= content->capacity)
	{
		if (!expand_capacity(content))
		{
			cleanup_content(content);
			return (NULL);
		}
	}
	content->lines[content->size] = NULL;
	result = content->lines;
	free(content);
	return (result);
}

char	**read_entire_file(int fd)
{
	t_file_content	*content;
	char			*line;

	if (fd < 0)
		return (NULL);
	content = init_file_content();
	if (!content)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(content, line))
		{
			free(line);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	return (finalize_content(content));
}
