/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:40:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:19:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Main drawing function that divides the map into sections
 *
 * @param ctx Context
 */
void	draw_lines(t_ctx *ctx)
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
