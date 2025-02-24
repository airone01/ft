/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:16:22 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 13:13:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file_content	*init_file_content(void)
{
	t_file_content	*content;

	content = malloc(sizeof(t_file_content));
	if (!content)
		return (NULL);
	content->lines = malloc(sizeof(char *) * RF_INITIAL_CAPACITY);
	if (!content->lines)
	{
		free(content);
		return (NULL);
	}
	content->size = 0;
	content->capacity = RF_INITIAL_CAPACITY;
	return (content);
}

int	expand_capacity(t_file_content *content)
{
	size_t	new_capacity;
	char	**new_lines;
	size_t	i;

	new_capacity = content->capacity * RF_GROWTH_FACTOR;
	new_lines = malloc(sizeof(char *) * new_capacity);
	if (!new_lines)
		return (0);
	i = 0;
	while (i < content->capacity)
	{
		new_lines[i] = content->lines[i];
		i++;
	}
	free(content->lines);
	content->lines = new_lines;
	content->capacity = new_capacity;
	return (1);
}

int	append_line(t_file_content *content, char *line)
{
	if (content->size >= content->capacity)
	{
		if (!expand_capacity(content))
			return (0);
	}
	content->lines[content->size++] = line;
	return (1);
}
