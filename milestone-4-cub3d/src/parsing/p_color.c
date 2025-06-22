/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:46:59 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 13:38:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static bool	parse_rgb_values(int *r, int *g, int *b, char *color)
{
	if (ft_isdigit(*color))
		*r = ft_atoi(color);
	while (*color && *color != ',')
		color++;
	if (!*color)
		return (true);
	color++;
	if (ft_isdigit(*color))
		*g = ft_atoi(color);
	while (*color && *color != ',')
		color++;
	if (!*color)
		return (true);
	color++;
	if (ft_isdigit(*color))
		*b = ft_atoi(color);
	return (false);
}

static bool	get_color_floor(t_data *data, char *color)
{
	int	r;
	int	g;
	int	b;

	r = -1;
	g = -1;
	b = -1;
	if (parse_rgb_values(&r, &g, &b, color))
	{
		data->error_detected = true;
		return (true);
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_printf(RED "Error\nColor values must be between 0-255\n" RESET);
		return (true);
	}
	data->floor_color.red = r;
	data->floor_color.green = g;
	data->floor_color.blue = b;
	return (false);
}

static bool	get_color_ceil(t_data *data, char *color)
{
	int	r;
	int	g;
	int	b;

	r = -1;
	g = -1;
	b = -1;
	if (parse_rgb_values(&r, &g, &b, color))
	{
		data->error_detected = true;
		return (true);
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_printf(RED "Error\nColor values must be between 0-255\n" RESET);
		return (true);
	}
	data->ceil_color.red = r;
	data->ceil_color.green = g;
	data->ceil_color.blue = b;
	return (false);
}

static bool	get_colors(t_data *data, char *color, const char *id)
{
	if (ft_strcmp(id, "F ") == 0)
	{
		data->color_f_found = true;
		if (get_color_floor(data, color))
			return (true);
		return (false);
	}
	if (ft_strcmp(id, "C ") == 0)
	{
		data->color_c_found = true;
		if (get_color_ceil(data, color))
			return (true);
		return (false);
	}
	return (true);
}

bool	parse_color_line(t_data *data, char *line, const char *id)
{
	char	*skip;
	char	*color;

	skip = line;
	while (*skip && (*skip == ' ' || *skip == '\t'))
		skip++;
	if (ft_strncmp(skip, id, 2) != 0)
		return (true);
	color = skip + 2;
	while (*color && (*color == ' ' || *color == '\t'))
		color++;
	if (check_color_line(data, color))
		return (true);
	if (get_colors(data, color, id))
		return (true);
	return (false);
}
