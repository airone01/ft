/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:46:09 by maximart          #+#    #+#             */
/*   Updated: 2025/06/20 19:38:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "texture.h"
#include "parsing.h"

bool	check_text_duplicate(t_data *data, const char *cardinal, char *exist)
{
	if (exist)
	{
		data->error_detected = true;
		ft_printf(RED "Error\nDuplicate texture for %s\n" RESET, cardinal);
		return (true);
	}
	return (false);
}

static bool	parse_texture_door(t_data *data, char *path, const char *cardinal)
{
	if (ft_strcmp(cardinal, "D ") == 0)
	{
		if (check_text_duplicate(data, cardinal, data->texture_door))
			return (true);
		data->texture_door = ft_strtrim(path, "\n");
		return (true);
	}
	return (false);
}

static bool	parse_texture_sprite(t_data *data, char *path, const char *cardinal)
{
	if (ft_strcmp(cardinal, "P ") == 0)
	{
		if (check_text_duplicate(data, cardinal, data->texture_sprite))
			return (true);
		data->texture_sprite = ft_strtrim(path, "\n");
		return (true);
	}
	return (false);
}

bool	parse_texture_path(t_data *data, char *line, const char *cardinal)
{
	char	*skip;
	char	*path;

	skip = line;
	while (*skip && (*skip == ' ' || *skip == '\t'))
		skip++;
	if (!ft_strncmp(skip, cardinal, ft_strlen(cardinal)))
	{
		path = skip + 2;
		while (*path && (*path == ' ' || *path == '\t'))
			path++;
		if (parse_texture_no_so(data, path, cardinal))
			return (false);
		if (parse_texture_we_ea(data, path, cardinal))
			return (false);
		if (parse_texture_door(data, path, cardinal))
			return (false);
		if (parse_texture_sprite(data, path, cardinal))
			return (false);
		return (false);
	}
	return (true);
}
