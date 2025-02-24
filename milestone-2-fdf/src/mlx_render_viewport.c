/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_viewport.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:47:23 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 17:47:29 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Checks if a point is within or near the viewport
 *
 * @param point The point to check
 * @param width Viewport width
 * @param height Viewport height
 * @param margin Extra margin around viewport to prevent edge artifacts
 * @return t_bool True if point is visible or close to visible
 */
static t_bool	is_point_in_viewport(t_point point, int width, int height,
		int margin)
{
	return (point.x >= -margin && point.x <= width + margin && point.y >=
		-margin && point.y <= height + margin);
}

/**
 * @brief Checks if a line is completely outside the viewport
 *
 * @param p1 First endpoint
 * @param p2 Second endpoint
 * @param width Viewport width
 * @param height Viewport height
 * @return t_bool True if line is completely outside and can be culled
 */
static t_bool	is_line_outside_viewport(t_point p1, t_point p2, int width,
		int height)
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
