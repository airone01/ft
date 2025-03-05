/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_section_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:22:21 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/05 13:23:11 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Prepares connection data for a rightward connection
 *
 * @param rc Rendering context
 * @param x Current x position
 * @param y Current y position
 * @param data Pointer to connection data struct
 * @return t_bool Whether the connection should be drawn
 */
t_bool	prepare_right_connection(t_render_context *rc, int x, int y,
		t_connection_data *data)
{
	int	next_x;

	next_x = x + rc->lod;
	if (next_x >= rc->ctx->map.width)
		return (false);
	data->current = get_projected_point(x, y, rc->ctx);
	data->down = get_projected_point(next_x, y, rc->ctx);
	data->current_color = rc->ctx->map.matrix[y][x].color;
	data->down_color = rc->ctx->map.matrix[y][next_x].color;
	data->current_z = rc->ctx->map.matrix[y][x].elevation;
	data->down_z = rc->ctx->map.matrix[y][next_x].elevation;
	return (!is_line_outside_viewport(data->current, data->down,
			rc->ctx->img.width, rc->ctx->img.height));
}

/**
 * @brief Prepares connection data for a downward connection
 *
 * @param rc Rendering context
 * @param x Current x position
 * @param y Current y position
 * @param data Pointer to connection data struct
 * @return t_bool Whether the connection should be drawn
 */
t_bool	prepare_down_connection(t_render_context *rc, int x, int y,
		t_connection_data *data)
{
	int	next_y;

	next_y = y + rc->lod;
	if (next_y >= rc->ctx->map.height)
		return (false);
	data->current = get_projected_point(x, y, rc->ctx);
	data->down = get_projected_point(x, next_y, rc->ctx);
	data->current_color = rc->ctx->map.matrix[y][x].color;
	data->down_color = rc->ctx->map.matrix[next_y][x].color;
	data->current_z = rc->ctx->map.matrix[y][x].elevation;
	data->down_z = rc->ctx->map.matrix[next_y][x].elevation;
	return (!is_line_outside_viewport(data->current, data->down,
			rc->ctx->img.width, rc->ctx->img.height));
}
