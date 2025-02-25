/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_scale.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:13:22 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 09:12:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	process_corner(t_point3d corner, t_app *ctx, t_point3d *min,
		t_point3d *max)
{
	t_point3d	p;
	t_point		proj;

	p = (t_point3d){corner.x * ctx->scale, corner.y * ctx->scale, corner.z};
	p = rotate_x(p, ctx->rot_x);
	p = rotate_y(p, ctx->rot_y);
	p = rotate_z(p, ctx->rot_z);
	proj = iso_project(p);
	if (proj.x < min->x)
		min->x = proj.x;
	if (proj.y < min->y)
		min->y = proj.y;
	if (proj.x > max->x)
		max->x = proj.x;
	if (proj.y > max->y)
		max->y = proj.y;
}

static void	get_projected_bounds(t_app *ctx, t_point3d *min, t_point3d *max)
{
	int			w;
	int			h;
	t_point3d	corners[4];
	int			i;

	w = ctx->map.width - 1;
	h = ctx->map.height - 1;
	corners[0] = (t_point3d){0, 0, ctx->map.matrix[0][0] * ctx->z_scale};
	corners[1] = (t_point3d){w, 0, ctx->map.matrix[0][w] * ctx->z_scale};
	corners[2] = (t_point3d){0, h, ctx->map.matrix[h][0] * ctx->z_scale};
	corners[3] = (t_point3d){w, h, ctx->map.matrix[h][w] * ctx->z_scale};
	*min = (t_point3d){DBL_MAX, DBL_MAX, DBL_MAX};
	*max = (t_point3d){-DBL_MAX, -DBL_MAX, -DBL_MAX};
	i = -1;
	while (++i < 4)
		process_corner(corners[i], ctx, min, max);
}

static void	adjust_scale(t_app *ctx, t_point3d *min, t_point3d *max)
{
	int		i;
	double	width;
	double	height;

	i = -1;
	while (++i < 3)
	{
		get_projected_bounds(ctx, min, max);
		width = max->x - min->x;
		height = max->y - min->y;
		if (width <= 0 || height <= 0)
			break ;
		ctx->scale *= fmin((IMG_WIDTH * 0.85) / width, (IMG_HEIGHT * 0.85)
				/ height);
	}
}

static void	set_initial_offsets(t_app *ctx, t_point3d min, t_point3d max)
{
	ctx->offset_x = (IMG_WIDTH - (max.x + min.x)) / 2;
	ctx->offset_y = (IMG_HEIGHT - (max.y + min.y)) / 2;
}

/**
 * @brief	Calculates the initial scale of the map.
 *
 * @param	ctx		The application context.
 */
void	calculate_initial_scale(t_app *ctx)
{
	t_point3d	min;
	t_point3d	max;

	ctx->scale = fmin(IMG_WIDTH / (double)ctx->map.width, IMG_HEIGHT
			/ (double)ctx->map.height);
	ctx->z_scale = 1.0;
	adjust_scale(ctx, &min, &max);
	get_projected_bounds(ctx, &min, &max);
	set_initial_offsets(ctx, min, max);
}
