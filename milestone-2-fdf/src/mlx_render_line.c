/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:40:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 09:02:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Draws the connections between points
 *
 * @param ctx Application context
 * @param current Current point
 * @param x Coordinate on the X-axis
 * @param y Coordinate on the Y-axis
 */
static void	draw_point_connections(t_app *ctx, t_point current, int x, int y)
{
	t_point	right;
	t_point	down;

	if (x < ctx->map.width - 1)
	{
		right = get_projected_point(x + 1, y, ctx);
		if (!is_line_outside_viewport(current, right, ctx->img.width,
				ctx->img.height))
			draw_line_img(ctx, current, right, color_get_line(ctx,
					ctx->map.matrix[y][x], ctx->map.matrix[y][x + 1]));
	}
	if (y < ctx->map.height - 1)
	{
		down = get_projected_point(x, y + 1, ctx);
		if (!is_line_outside_viewport(current, down, ctx->img.width,
				ctx->img.height))
			draw_line_img(ctx, current, down, color_get_line(ctx,
					ctx->map.matrix[y][x], ctx->map.matrix[y + 1][x]));
	}
}

/**
 * @brief Renders a single section of the map
 *
 * @param ctx Application context
 * @param section The section to render
 */
static void	render_section(t_app *ctx, t_section section)
{
	t_point	current;
	int		x;
	int		y;

	y = section.start_y;
	while (y <= section.end_y)
	{
		x = section.start_x;
		while (x <= section.end_x)
		{
			current = get_projected_point(x, y, ctx);
			draw_point_connections(ctx, current, x, y);
			x++;
		}
		y++;
	}
}

/**
 * @brief Main drawing function that divides the map into sections
 *
 * @param ctx Application context
 */
void	draw_lines(t_app *ctx)
{
	t_section	section;
	int			section_start_y;
	int			section_start_x;
	int			section_size;

	section_size = 16;
	section_start_y = 0;
	while (section_start_y < ctx->map.height)
	{
		section.start_y = section_start_y;
		section.end_y = (int)fmin(section_start_y + section_size - 1,
				ctx->map.height - 1);
		section_start_x = 0;
		while (section_start_x < ctx->map.width)
		{
			section.start_x = section_start_x;
			section.end_x = (int)fmin(section_start_x + section_size - 1,
					ctx->map.width - 1);
			if (!is_section_outside_viewport(ctx, section))
				render_section(ctx, section);
			section_start_x += section_size;
		}
		section_start_y += section_size;
	}
}
