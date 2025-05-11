/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_viewport.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:47:23 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 19:01:07 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// /**
//  * @brief Checks if a point is within or near the viewport
//  *
//  * @param point The point to check
//  * @param width Viewport width
//  * @param height Viewport height
//  * @param margin Extra margin around viewport to prevent edge artifacts
//  * @return bool True if point is visible or close to visible
//  */
// static bool	is_point_in_viewport(t_point point, int width, int height,
// 		int margin)
// {
// 	return (point.x >= -margin && point.x <= width + margin && point.y >=
// 		-margin && point.y <= height + margin);
// }

/**
 * @brief Checks if a line is completely outside the viewport
 *
 * @param p1 First endpoint
 * @param p2 Second endpoint
 * @param width Viewport width
 * @param height Viewport height
 * @return bool True if line is completely outside and can be culled
 */
bool	is_line_outside_viewport(t_point p1, t_point p2, int width, int height)
{
	if (p1.x < 0 && p2.x < 0)
		return (true);
	if (p1.x > width && p2.x > width)
		return (true);
	if (p1.y < 0 && p2.y < 0)
		return (true);
	if (p1.y > height && p2.y > height)
		return (true);
	return (false);
}

/**
 * @brief Determines if an entire section is outside the viewport
 *
 * @param ctx Application context
 * @param section The section to check
 * @return bool True if the section is completely outside the viewport
 */
bool	is_section_outside_viewport(t_app *ctx, t_section section)
{
	t_point	corners[4];
	int		margin;
	int		width;
	int		height;

	margin = ctx->lod_level * 2;
	width = ctx->img.width;
	height = ctx->img.height;
	corners[0] = get_projected_point(section.start_x, section.start_y, ctx);
	corners[1] = get_projected_point(section.end_x, section.start_y, ctx);
	corners[2] = get_projected_point(section.start_x, section.end_y, ctx);
	corners[3] = get_projected_point(section.end_x, section.end_y, ctx);
	if ((corners[0].x < -margin && corners[1].x < -margin && corners[2].x <
			-margin && corners[3].x < -margin) || (corners[0].x > width + margin
			&& corners[1].x > width + margin && corners[2].x > width + margin
			&& corners[3].x > width + margin) || (corners[0].y < -margin
			&& corners[1].y < -margin && corners[2].y < -margin
			&& corners[3].y < -margin) || (corners[0].y > height + margin
			&& corners[1].y > height + margin && corners[2].y > height + margin
			&& corners[3].y > height + margin))
		return (true);
	return (false);
}
