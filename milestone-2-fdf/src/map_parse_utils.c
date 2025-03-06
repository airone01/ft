/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:22:42 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/06 10:20:35 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Count the number of columns (numbers) in a line
 *
 * @param line The line to count columns in
 * @return int Number of columns
 */
int	count_columns_in_line(const char *line)
{
	const char	*ptr;
	t_bool		in_number;
	int			col;

	col = 0;
	ptr = line;
	in_number = false;
	if (!line)
		return (0);
	while (*ptr && *ptr != '\n')
	{
		if (ft_isspace(*ptr))
		{
			if (in_number)
				in_number = false;
		}
		else if (!in_number)
		{
			in_number = true;
			col += 1;
		}
		ptr++;
	}
	return (col);
}

/**
 * @brief Process a token to extract elevation and optional color
 *
 * @param ctx Application context
 * @param token Token string to process
 * @param row Current row being processed
 * @param col Pointer to current column index
 */
void	parse_token(t_app *ctx, char *token, int row, int *col)
{
	int				val;
	unsigned int	color;
	char			*color_part;

	val = ft_atoi(token);
	color = 0;
	color_part = ft_strchr(token, ',');
	if (color_part)
	{
		if (!parse_color(ctx, color_part + 1, &color))
			exit_error(ctx, ERR_MAP_INVALID_COLOR);
	}
	if (*col < ctx->map.width)
	{
		ctx->map.matrix[row][*col].elevation = val;
		ctx->map.matrix[row][*col].color = color;
		(*col)++;
	}
}
