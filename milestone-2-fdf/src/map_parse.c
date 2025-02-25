/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:49:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 09:13:01 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	process_number(t_app *ctx, const char **ptr, int row, int *col)
{
	int	val;

	while (**ptr && ft_isspace(**ptr))
		(*ptr)++;
	if (!**ptr || **ptr == '\n')
		return ;
	val = fast_atoi(ptr);
	while (**ptr && !ft_isspace(**ptr))
		(*ptr)++;
	ctx->map.matrix[row][(*col)++] = val;
}

static void	validate_line_format(t_app *ctx, const char *line, int row)
{
	int	col;

	col = count_columns_in_line(line);
	if (col == 0)
	{
		ft_printf("Error on line %d: Empty line\n", row + 1);
		exit_error(ctx, ERR_MAP_EMPTY_LINE);
	}
	if (ctx->map.width == -1)
		ctx->map.width = col;
	else if (col != ctx->map.width)
	{
		ft_printf("Error on line %d: Got %d columns but expected %d\n", row,
			col, ctx->map.width);
		exit_error(ctx, ERR_MAP_IRREGULAR);
	}
}

static void	parse_line(t_app *ctx, const char *line, int *row)
{
	int			col;
	const char	*ptr;
	const char	*end;

	validate_line_format(ctx, line, *row);
	ptr = line;
	end = line + strlen(line);
	col = 0;
	while (ptr < end && *ptr)
	{
		process_number(ctx, &ptr, *row, &col);
		while (ptr < end && *ptr && ft_isspace(*ptr) && *ptr != '\n')
			ptr++;
	}
	(*row)++;
}

/**
 * @brief	Parses the map content.
 *
 * @param	ctx		The application context.
 * @param	content	The content of the map file.
 */
void	map_parse(t_app *ctx)
{
	char	**ptr;
	int		row;

	if (!ctx->file_content || !*ctx->file_content)
		exit_error(ctx, ERR_FILE_EMPTY);
	ptr = ctx->file_content;
	row = 0;
	ctx->map.min_elevation = INT_MAX;
	ctx->map.max_elevation = INT_MIN;
	while (*ptr)
	{
		parse_line(ctx, *ptr, &row);
		ptr++;
	}
	if (row == 0)
		exit_error(ctx, ERR_FILE_EMPTY);
}
