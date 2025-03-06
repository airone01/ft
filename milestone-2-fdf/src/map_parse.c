/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:49:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/05 13:46:51 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

/**
 * @brief Parse a line from the map file and store values in matrix
 *
 * @param ctx Application context
 * @param line Line to parse
 * @param row Pointer to current row index
 */
static void	parse_line(t_app *ctx, const char *line, int *row)
{
	char	**tokens;
	int		col;
	int		i;

	validate_line_format(ctx, line, *row);
	tokens = ft_split((char *)line, ' ');
	if (!tokens)
		exit_error(ctx, ERR_MALLOC);
	col = 0;
	i = 0;
	while (tokens[i] && col < ctx->map.width)
	{
		if (tokens[i][0] != '\0')
		{
			parse_token(ctx, tokens[i], *row, &col);
		}
		i++;
	}
	free_2d_array((void **)tokens);
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
