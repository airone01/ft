/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:44:41 by maximart          #+#    #+#             */
/*   Updated: 2025/06/20 19:34:00 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mem.h"
#include "parsing.h"

bool	process_config_line(t_data *data, char *line)
{
	if (!parse_texture_path(data, line, "NO "))
		return (false);
	if (!parse_texture_path(data, line, "SO "))
		return (false);
	if (!parse_texture_path(data, line, "WE "))
		return (false);
	if (!parse_texture_path(data, line, "EA "))
		return (false);
	if (!parse_texture_path(data, line, "D "))
		return (false);
	if (!parse_color_line(data, line, "F "))
		return (false);
	if (!parse_color_line(data, line, "C "))
		return (false);
	if (!parse_texture_path(data, line, "P "))
		return (false);
	return (true);
}

static int	read_file_content(int fd, t_data *data, t_map_buffer *buffer)
{
	char	*line;
	bool	map_section_started;

	map_section_started = false;
	line = get_next_line(fd);
	while (line)
	{
		if (process_single_line(data, line, &map_section_started, buffer)
			|| data->error_detected)
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!map_section_started)
	{
		ft_printf(RED "Error\nNo valid map found in file\n" RESET);
		return (1);
	}
	return (0);
}

int	read_file(t_data *data, const char *file)
{
	t_map_buffer	map_buffer;
	int				result;
	int				fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (init_map_buffer(&map_buffer))
	{
		close(fd);
		return (1);
	}
	result = read_file_content(fd, data, &map_buffer);
	close(fd);
	if (result != 0 || buffer_to_data(data, &map_buffer))
	{
		free_map_buffer(&map_buffer);
		return (1);
	}
	free_map_buffer(&map_buffer);
	return (0);
}
