/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:22:42 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/05 13:44:56 by elagouch         ###   ########.fr       */
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
 * @brief Convert a hex character to its integer value
 * @param c Hexadecimal character (0-9, a-f, A-F)
 * @return int Corresponding integer value (0-15)
 */
int	hex_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

/**
 * Checks if a character is a hexadecimal digit (0-9, a-f, A-F)
 * @param c The character to check
 * @return 1 if the character is a hexadecimal digit, 0 otherwise
 */
int	ft_ishexdigit(int c)
{
	int	is_digit;
	int	is_lower_hex;
	int	is_upper_hex;

	is_digit = (c >= '0' && c <= '9');
	is_lower_hex = (c >= 'a' && c <= 'f');
	is_upper_hex = (c >= 'A' && c <= 'F');
	return (is_digit || is_lower_hex || is_upper_hex);
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

/**
 * @brief Parse color value from hex string
 *
 * @param ctx Application context
 * @param str Color string to parse
 * @param color Pointer to store parsed color
 * @return t_bool Success or failure
 */
t_bool	parse_color(t_app *ctx, char *str, unsigned int *color)
{
	int	i;

	(void)ctx;
	if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
		return (false);
	str += 2;
	*color = 0;
	i = 0;
	while (str[i] && ft_ishexdigit(str[i]))
	{
		*color = *color * 16 + (unsigned int)hex_value(str[i]);
		i++;
	}
	if (str[i] && !ft_isspace(str[i]) && str[i] != '\0')
		return (false);
	return (true);
}
