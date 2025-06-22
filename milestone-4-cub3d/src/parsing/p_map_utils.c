/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:20:23 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 13:39:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

bool	expand_buffer(t_map_buffer *buffer)
{
	char	**new_lines;
	int		i;

	buffer->capacity *= 2;
	new_lines = ft_calloc(buffer->capacity, sizeof(char *));
	if (!new_lines)
		return (true);
	i = 0;
	while (i < buffer->count)
	{
		new_lines[i] = buffer->lines[i];
		i++;
	}
	free(buffer->lines);
	buffer->lines = new_lines;
	return (false);
}

bool	add_line_to_buffer(t_map_buffer *buffer, char *line)
{
	int	len;

	if (buffer->count >= buffer->capacity)
	{
		if (expand_buffer(buffer))
			return (true);
	}
	buffer->lines[buffer->count] = ft_strdup(line);
	if (!buffer->lines[buffer->count])
		return (true);
	len = (int)ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	if (len > buffer->max_width)
		buffer->max_width = len;
	buffer->count++;
	return (false);
}

void	free_map_buffer(t_map_buffer *buffer)
{
	int	i;

	if (!buffer->lines)
		return ;
	i = 0;
	while (i < buffer->count)
	{
		if (buffer->lines[i])
			free(buffer->lines[i]);
		i++;
	}
	free(buffer->lines);
	buffer->lines = NULL;
}

bool	buffer_to_data(t_data *data, t_map_buffer *buffer)
{
	int	i;

	data->map_height = buffer->count;
	data->map_width = buffer->max_width;
	data->map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!data->map)
		return (true);
	i = 0;
	while (i < buffer->count)
	{
		data->map[i] = buffer->lines[i];
		buffer->lines[i] = NULL;
		i++;
	}
	data->map[i] = NULL;
	return (false);
}
