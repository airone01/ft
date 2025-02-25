/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_section.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:04:12 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 13:50:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Draws a connection to the right point if it exists and is visible
 *
 * @param rc Rendering context
 * @param x Current x position
 * @param y Current y position
 * @param is_edge Whether the point is on the edge of a section
 */
static void	draw_right_connection(t_render_context *rc, int x, int y,
		t_bool is_edge)
{
	t_point	current;
	t_point	right;
	int		next_x;

	(void)is_edge;
	next_x = x + rc->lod;
	if (next_x < rc->ctx->map.width)
	{
		current = get_projected_point(x, y, rc->ctx);
		right = get_projected_point(next_x, y, rc->ctx);
		if (!is_line_outside_viewport(current, right, rc->ctx->img.width,
				rc->ctx->img.height))
		{
			draw_line_img(rc->ctx, current, right, color_get_line(rc->ctx,
					rc->ctx->map.matrix[y][x], rc->ctx->map.matrix[y][next_x]));
		}
	}
}

/**
 * @brief Draws a connection to the down point if it exists and is visible
 *
 * @param rc Rendering context
 * @param x Current x position
 * @param y Current y position
 * @param is_edge Whether the point is on the edge of a section
 */
static void	draw_down_connection(t_render_context *rc, int x, int y,
		t_bool is_edge)
{
	t_point	current;
	t_point	down;
	int		next_y;

	(void)is_edge;
	next_y = y + rc->lod;
	if (next_y < rc->ctx->map.height)
	{
		current = get_projected_point(x, y, rc->ctx);
		down = get_projected_point(x, next_y, rc->ctx);
		if (!is_line_outside_viewport(current, down, rc->ctx->img.width,
				rc->ctx->img.height))
		{
			draw_line_img(rc->ctx, current, down, color_get_line(rc->ctx,
					rc->ctx->map.matrix[y][x], rc->ctx->map.matrix[next_y][x]));
		}
	}
}

/**
 * @brief Conditions to render a connection or not
 *
 * @param p Function parameters
 */
static void	render_section_loop(t_render_section_params p)
{
	while (p.x <= p.section.end_x)
	{
		p.is_edge_x = (p.x == p.section.end_x);
		if (!p.is_edge_x)
			draw_right_connection(&p.rc, p.x, p.y, p.is_edge_x);
		else if (p.x + p.rc.lod < p.ctx->map.width)
			draw_right_connection(&p.rc, p.x, p.y, p.is_edge_x);
		if (!p.is_edge_y)
			draw_down_connection(&p.rc, p.x, p.y, p.is_edge_y);
		else if (p.y + p.rc.lod < p.ctx->map.height)
			draw_down_connection(&p.rc, p.x, p.y, p.is_edge_y);
		p.x += p.rc.lod;
	}
}

/**
 * @brief Renders a single section of the map with proper edge connections
 *
 * @param ctx Application context
 * @param section The section to render
 */
void	render_section(t_app *ctx, t_section section)
{
	t_render_context	rc;
	int					x;
	int					y;
	t_bool				is_edge_x;
	t_bool				is_edge_y;

	rc.ctx = ctx;
	rc.section = section;
	rc.lod = ctx->lod_level;
	y = section.start_y;
	is_edge_x = false;
	is_edge_y = false;
	while (y <= section.end_y)
	{
		is_edge_y = (y == section.end_y);
		x = section.start_x;
		render_section_loop((t_render_section_params){rc, section, is_edge_x,
			is_edge_y, ctx, x, y});
		y += rc.lod;
	}
}
