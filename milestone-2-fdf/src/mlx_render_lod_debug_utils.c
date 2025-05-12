/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_lod_debug_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:48:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:21:32 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Display LOD information text line by line
 *
 * @param ctx Context
 * @param msg Message text to display
 * @param y_pos Vertical position for the text
 */
void	put_debug_text(t_ctx *ctx, char *msg, int y_pos)
{
	mlx_string_put(ctx->mlx, ctx->win, 10, y_pos, 0x00FFFFFF, msg);
}

static bool	append_int_init(int *n, int *i, int max_len, char *str)
{
	if (*n == 0)
	{
		if (max_len > 0)
			str[0] = '0';
		return (true);
	}
	*i = 0;
	if (*n < 0)
	{
		if (max_len > 0)
			str[*i++] = '-';
		*n = -*n;
	}
	return (false);
}

/**
 * @brief Append an integer to a string buffer without allocation
 *
 * @param str The destination string buffer
 * @param n The integer to append
 * @param max_len Maximum buffer length
 * @return Number of characters written
 */
int	append_int(char *str, int n, int max_len)
{
	int		len;
	int		i;
	int		tmp;
	char	digits[12];

	if (append_int_init(&n, &i, max_len, str))
		return (1);
	len = 0;
	tmp = n;
	while (tmp > 0)
	{
		digits[len++] = (char)((tmp % 10) + '0');
		tmp /= 10;
	}
	while (len > 0 && i < max_len)
		str[i++] = digits[--len];
	return (i);
}

/**
 * @brief Append a double to a string buffer with 2 decimal places
 *
 * @param str The destination string buffer
 * @param val The double value to append
 * @param max_len Maximum buffer length
 * @return Number of characters written
 */
int	append_double(char *str, double val, int max_len)
{
	int	i;
	int	whole;
	int	decimal;

	whole = (int)val;
	i = append_int(str, whole, max_len);
	if (i < max_len - 1)
		str[i++] = '.';
	decimal = (int)((val - whole) * 100);
	if (decimal < 0)
		decimal = -decimal;
	if (decimal < 10 && i < max_len - 1)
		str[i++] = '0';
	if (i < max_len)
		i += append_int(str + i, decimal, max_len - i);
	return (i);
}
