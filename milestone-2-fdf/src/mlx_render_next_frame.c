/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_next_frame.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 10:56:00 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Helper function to project a 3D point to 2D with scaling and offset
 */
t_point	get_projected_point(int x, int y, t_app *ctx)
{
	t_point3d	point3d;
	t_point		projected;

	point3d.x = x * ctx->scale;
	point3d.y = y * ctx->scale;
	point3d.z = ctx->map.matrix[y][x] * ctx->z_scale;
	point3d = rotate_x(point3d, ctx->rot_x);
	point3d = rotate_y(point3d, ctx->rot_y);
	point3d = rotate_z(point3d, ctx->rot_z);
	projected = iso_project(point3d);
	projected = point_add(projected, (t_point){ctx->offset_x, ctx->offset_y});
	return (projected);
}

/**
 * @brief Renders the next frame
 *
 * @param ctx	Application context
 */
int	render_next_frame(t_app *ctx)
{
	if (!ctx->needs_render)
		return (0);
	if (!ctx->img.img)
	{
		ctx->img.img = mlx_new_image(ctx->mlx, ctx->img.width, ctx->img.height);
		ctx->img.addr = mlx_get_data_addr(ctx->img.img,
				&ctx->img.bits_per_pixel, &ctx->img.line_length,
				&ctx->img.endian);
		ft_memset(ctx->img.addr, 0, (size_t)(ctx->img.height
				* ctx->img.line_length));
	}
	else
		ft_memset(ctx->img.addr, 0, (size_t)(ctx->img.height
				* ctx->img.line_length));
	draw_lines(ctx);
	if (ctx->debug_mode & DEBUG_SECTIONS)
		render_section_debug(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->img.img, 0, 0);
	ctx->needs_render = false;
	return (0);
}
