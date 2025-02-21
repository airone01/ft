/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:49:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 22:56:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	process_number(t_app *app, const char **ptr, int row, int *col)
{
	int	val;

	val = fast_atoi(ptr);
	app->map.matrix[row][(*col)++] = val;
	app->map.min_elevation = (int)ft_min((long)app->map.min_elevation,
			(long)val);
	app->map.max_elevation = (int)ft_max((long)app->map.max_elevation,
			(long)val);
}

static void	parse_line(t_app *app, const char **ptr, int *row)
{
	int	col;

	col = 0;
	while (**ptr && **ptr != '\n')
	{
		process_number(app, ptr, *row, &col);
		while (**ptr && !ft_isspace(**ptr))
			(*ptr)++;
		while (ft_isspace(**ptr))
			(*ptr)++;
	}
	if (app->map.width == -1)
		app->map.width = col;
	(*row)++;
}

/**
 * @brief	Parses the map content.
 *
 * @param	app		The application context.
 * @param	content	The content of the map file.
 */
void	map_parse(t_app *app, char *content)
{
	const char	*ptr = content;
	int			row;

	row = 0;
	app->map.min_elevation = INT_MAX;
	app->map.max_elevation = INT_MIN;
	while (*ptr)
	{
		parse_line(app, &ptr, &row);
		if (*ptr)
			ptr++;
	}
}
