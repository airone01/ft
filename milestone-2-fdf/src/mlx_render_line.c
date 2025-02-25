/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:40:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 09:24:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Draws a connection to the right point with LOD
 *
 * @param rc Rendering context
 * @param x Current x position
 * @param y Current y position
 */
static void	draw_right_connection(t_render_context *rc, int x, int y)
{
	t_point	current;
	t_point	right;

	if (x + rc->lod <= rc->section.end_x && x + rc->lod < rc->ctx->map.width)
	{
		current = get_projected_point(x, y, rc->ctx);
		right = get_projected_point(x + rc->lod, y, rc->ctx);
		if (!is_line_outside_viewport(current, right, rc->ctx->img.width,
				rc->ctx->img.height))
			draw_line_img(rc->ctx, current, right, color_get_line(rc->ctx,
					rc->ctx->map.matrix[y][x], rc->ctx->map.matrix[y][x
					+ rc->lod]));
	}
}

/**
 * @brief Draws a connection to the down point with LOD
 *
 * @param rc Rendering context
 * @param x Current x position
 * @param y Current y position
 */
static void	draw_down_connection(t_render_context *rc, int x, int y)
{
	t_point	current;
	t_point	down;

	if (y + rc->lod <= rc->section.end_y && y + rc->lod < rc->ctx->map.height)
	{
		current = get_projected_point(x, y, rc->ctx);
		down = get_projected_point(x, y + rc->lod, rc->ctx);
		if (!is_line_outside_viewport(current, down, rc->ctx->img.width,
				rc->ctx->img.height))
			draw_line_img(rc->ctx, current, down, color_get_line(rc->ctx,
					rc->ctx->map.matrix[y][x], rc->ctx->map.matrix[y
					+ rc->lod][x]));
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
	t_render_context	rc;
	int					x;
	int					y;

	rc.ctx = ctx;
	rc.section = section;
	rc.lod = ctx->lod_level;
	if (rc.lod == 0)
		rc.lod = get_appropriate_lod(ctx);
	y = section.start_y;
	while (y <= section.end_y)
	{
		x = section.start_x;
		while (x <= section.end_x)
		{
			draw_right_connection(&rc, x, y);
			draw_down_connection(&rc, x, y);
			x += rc.lod;
		}
		y += rc.lod;
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
