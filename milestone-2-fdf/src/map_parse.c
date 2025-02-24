/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:49:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 17:17:55 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	process_number(t_app *app, const char **ptr, int row, int *col)
{
	int	val;

	while (**ptr && ft_isspace(**ptr))
		(*ptr)++;
	if (!**ptr || **ptr == '\n')
		return ;
	val = fast_atoi(ptr);
	while (**ptr && !ft_isspace(**ptr))
		(*ptr)++;
	app->map.matrix[row][(*col)++] = val;
}

static int	count_columns_in_line(const char *line)
{
	int			col;
	const char	*ptr;

	col = 0;
	ptr = line;
	while (*ptr && ft_isspace(*ptr))
		ptr++;
	if (!*ptr || *ptr == '\n')
		return (0);
	while (*ptr)
	{
		if (!ft_isspace(*ptr))
		{
			col++;
			while (*ptr && !ft_isspace(*ptr))
				ptr++;
		}
		else
		{
			while (*ptr && ft_isspace(*ptr))
				ptr++;
		}
	}
	return (col);
}

static void	validate_line_format(t_app *app, const char *line, int row)
{
	int	col;

	col = count_columns_in_line(line);
	if (col == 0)
	{
		ft_printf("Error on line %d: Empty line\n", row + 1);
		exit_error(app, ERR_MAP_EMPTY_LINE);
	}
	if (app->map.width == -1)
		app->map.width = col;
	else if (col != app->map.width)
	{
		ft_printf("Error on line %d: Got %d columns but expected %d\n", row,
			col, app->map.width);
		exit_error(app, ERR_MAP_IRREGULAR);
	}
}

static void	parse_line(t_app *app, const char *line, int *row)
{
	int			col;
	const char	*ptr;
	const char	*end;

	validate_line_format(app, line, *row);
	ptr = line;
	end = line + strlen(line);
	col = 0;
	while (ptr < end && *ptr)
	{
		process_number(app, &ptr, *row, &col);
		while (ptr < end && *ptr && ft_isspace(*ptr) && *ptr != '\n')
			ptr++;
	}
	(*row)++;
}

/**
 * @brief	Parses the map content.
 *
 * @param	app		The application context.
 * @param	content	The content of the map file.
 */
void	map_parse(t_app *app)
{
	char	**ptr;
	int		row;

	if (!app->file_content || !*app->file_content)
		exit_error(app, ERR_FILE_EMPTY);
	ptr = app->file_content;
	row = 0;
	app->map.min_elevation = INT_MAX;
	app->map.max_elevation = INT_MIN;
	while (*ptr)
	{
		parse_line(app, *ptr, &row);
		ptr++;
	}
	if (row == 0)
		exit_error(app, ERR_FILE_EMPTY);
}
