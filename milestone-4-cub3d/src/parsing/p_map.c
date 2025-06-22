/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:57:14 by maximart          #+#    #+#             */
/*   Updated: 2025/06/20 19:33:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "utils.h"

static bool	is_config_line(char *line)
{
	char	*trimmed;

	if (!line)
		return (false);
	trimmed = line;
	while (*trimmed && (*trimmed == ' ' || *trimmed == '\t'))
		trimmed++;
	return (config_line_condition(trimmed));
}

bool	looks_like_map_line(char *line)
{
	char	*tmp;

	if (!line || line[0] == '\0')
		return (false);
	tmp = line;
	while (*tmp && (*tmp == ' ' || *tmp == '\t'))
		tmp++;
	if (*tmp == '\0' || *tmp == '\n')
		return (false);
	if (is_config_line(line))
		return (false);
	while (*tmp && *tmp != '\n')
	{
		if (ft_strchr(map_chars(), *tmp))
			return (true);
		tmp++;
	}
	return (false);
}

bool	process_single_line(t_data *data, char *line, bool *map_section_started,
		t_map_buffer *buffer)
{
	if (!*map_section_started)
	{
		if (looks_like_map_line(line))
		{
			*map_section_started = true;
			if (add_line_to_buffer(buffer, line))
				return (true);
		}
		else if (is_config_line(line))
		{
			if (process_config_line(data, line))
				return (true);
		}
	}
	else
	{
		if (add_line_to_buffer(buffer, line))
			return (true);
	}
	return (false);
}
