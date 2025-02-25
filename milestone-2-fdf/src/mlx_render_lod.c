/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_lod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:10:27 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 11:44:32 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Displays numeric LOD debug info using mlx_string_put
 *
 * @param ctx Application context
 * @param value Numeric value to display
 * @param label Label text
 * @param y_pos Vertical position for the text
 */
void	put_debug_number(t_app *ctx, double value, char *label, int y_pos)
{
	char	num_str[16];
	char	full_str[64];
	int		i;
	int		decimal_part;
	int		whole_part;

	whole_part = (int)value;
	decimal_part = (int)((value - whole_part) * 100);
	if (decimal_part < 0)
		decimal_part = -decimal_part;
	ft_strlcpy(num_str, ft_itoa(whole_part), 16);
	ft_strlcat(num_str, (char *)".", 16);
	if (decimal_part < 10)
		ft_strlcat(num_str, (char *)"0", 16);
	ft_strlcat(num_str, ft_itoa(decimal_part), 16);
	i = 0;
	while (i < 64)
	{
		full_str[i] = '\0';
		i++;
	}
	ft_strlcpy(full_str, label, 64);
	ft_strlcat(full_str, num_str, 64);
	mlx_string_put(ctx->mlx, ctx->win, 10, y_pos, 0x00FFFFFF, full_str);
}

/**
 * @brief Calculates map diagonal size for LOD determination
 *
 * @param width Map width
 * @param height Map height
 * @return double The diagonal length
 */
static double	calc_map_diagonal(int width, int height)
{
	double	w_squared;
	double	h_squared;

	w_squared = (double)width * (double)width;
	h_squared = (double)height * (double)height;
	return (sqrt(w_squared + h_squared));
}

/**
 * @brief Calculates effective scale factoring in map and viewport size
 *
 * @param ctx Application context
 * @param map_diagonal Diagonal size of the map
 * @return double The effective scale value
 */
static double	calc_effective_scale(t_app *ctx, double map_diagonal)
{
	double	view_size;
	double	effective_scale;

	view_size = fmin(ctx->img.width, ctx->img.height);
	effective_scale = ctx->scale * view_size / map_diagonal;
	return (effective_scale);
}

/**
 * @brief Improved function to determine appropriate LOD based on scale
 * and map size
 *
 * @param ctx Application context
 * @return int The appropriate LOD level
 */
int	get_appropriate_lod(t_app *ctx)
{
	double	map_diagonal;
	double	effective_scale;
	char	buffer[64];
	int		i;

	map_diagonal = calc_map_diagonal(ctx->map.width, ctx->map.height);
	effective_scale = calc_effective_scale(ctx, map_diagonal);
	if (ctx->debug_mode & DEBUG_LOD)
	{
		i = 0;
		while (i < 64)
			buffer[i++] = '\0';
		ft_strlcpy(buffer, "Effective Scale: ", 64);
		i = (int)ft_strlen(buffer);
		append_double(buffer + i, effective_scale, 64 - i);
		mlx_string_put(ctx->mlx, ctx->win, 10, 20, 0x00FFFFFF, buffer);
	}
	if (effective_scale < 0.15)
		return (LOD_VERY_LOW);
	else if (effective_scale < 0.4)
		return (LOD_LOW);
	else if (effective_scale < 0.8)
		return (LOD_MEDIUM);
	else
		return (LOD_HIGH);
}
