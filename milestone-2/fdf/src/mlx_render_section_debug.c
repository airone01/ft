/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_section_debug.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:50:07 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:19:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Draws a rectangle outline for a section boundary
 *
 * @param ctx Context
 * @param section Section to draw outline for
 * @param color Color of the outline
 */
void	draw_section_outline(t_ctx *ctx, t_section section, unsigned int color)
{
	t_point	corners[4];
	int		i;

	corners[0] = get_projected_point(section.start_x, section.start_y, ctx);
	corners[1] = get_projected_point(section.end_x, section.start_y, ctx);
	corners[2] = get_projected_point(section.end_x, section.end_y, ctx);
	corners[3] = get_projected_point(section.start_x, section.end_y, ctx);
	i = 0;
	while (i < 4)
	{
		draw_line_img(ctx, corners[i], corners[(i + 1) % 4], color);
		i++;
	}
}

/**
 * @brief Renders debug visualization of section boundaries
 *
 * @param ctx Context
 */
void	render_section_debug(t_ctx *ctx)
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
				draw_section_outline(ctx, section, 0x00FF00FF);
			section_start_x += section_size;
		}
		section_start_y += section_size;
	}
}
