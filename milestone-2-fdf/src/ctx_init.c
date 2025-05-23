/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:12:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:19:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ctx_init_img(t_ctx *ctx)
{
	ctx->img.addr = NULL;
	ctx->img.img = NULL;
	ctx->img.bits_per_pixel = 0;
	ctx->img.line_length = 0;
	ctx->img.endian = 0;
	ctx->img.width = IMG_WIDTH;
	ctx->img.height = IMG_HEIGHT;
	ctx->offset_x = ctx->img.width / 2;
	ctx->offset_y = ctx->img.height / 3;
}

/**
 * @brief	Initialize the global ctx structure.
 */
t_ctx	*ctx_init(void)
{
	t_ctx	*ctx;

	ctx = safe_calloc(NULL, 1, sizeof(t_ctx));
	ctx->projection_type = PROJECTION_ISOMETRIC;
	ctx->horizon_distance = 1000.0;
	ctx->debug_mode = DEBUG_NONE;
	ctx->map.min_elevation = 0;
	ctx->map.max_elevation = 0;
	ctx->lod_level = LOD_HIGH;
	ctx->needs_render = true;
	ctx->file_content = NULL;
	ctx->map.matrix = NULL;
	ctx->color_scheme = 0;
	ctx->map.height = 0;
	ctx->map.width = -1;
	ctx->z_scale = 1.0;
	ctx->file_fd = -1;
	ctx->scale = 1.0;
	ctx->rot_x = 0.0;
	ctx->rot_y = 0.0;
	ctx->rot_z = 0.0;
	ctx->mlx = NULL;
	ctx->win = NULL;
	ctx_init_img(ctx);
	return (ctx);
}
