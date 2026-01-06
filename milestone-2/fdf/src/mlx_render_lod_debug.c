/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_lod_debug.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:13:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:19:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Prepare and display LOD level text
 *
 * @param ctx Context
 * @param lod Current LOD level
 * @param y_pos Vertical position for the text
 */
static void	put_lod_level(t_ctx *ctx, int lod, int y_pos)
{
	char	buffer[64];
	int		i;

	i = 0;
	while (i < 64)
		buffer[i++] = '\0';
	ft_strlcpy(buffer, "LOD Level: 1/", 64);
	i = (int)ft_strlen(buffer);
	append_int(buffer + i, lod, 64 - i);
	put_debug_text(ctx, buffer, y_pos);
}

/**
 * @brief Prepare and display map dimensions
 *
 * @param ctx Context
 * @param y_pos Vertical position for the text
 */
static void	put_map_size(t_ctx *ctx, int y_pos)
{
	char	buffer[64];
	int		i;
	int		len;

	i = 0;
	while (i < 64)
		buffer[i++] = '\0';
	ft_strlcpy(buffer, "Map Size: ", 64);
	i = (int)ft_strlen(buffer);
	len = append_int(buffer + i, ctx->map.width, 64 - i);
	i += len;
	if (i < 63)
		buffer[i++] = 'x';
	append_int(buffer + i, ctx->map.height, 64 - i);
	put_debug_text(ctx, buffer, y_pos);
}

/**
 * @brief Prepare and display scale value
 *
 * @param ctx Context
 * @param y_pos Vertical position for the text
 */
static void	put_scale(t_ctx *ctx, int y_pos)
{
	char	buffer[64];
	int		i;

	i = 0;
	while (i < 64)
		buffer[i++] = '\0';
	ft_strlcpy(buffer, "Scale: ", 64);
	i = (int)ft_strlen(buffer);
	append_double(buffer + i, ctx->scale, 64 - i);
	put_debug_text(ctx, buffer, y_pos);
}

/**
 * @brief Prepare and display projection type text
 *
 * @param ctx Context
 * @param y_pos Vertical position for the text
 */
static void	put_projection_type(t_ctx *ctx, int y_pos)
{
	char	buffer[64];
	int		i;

	i = 0;
	while (i < 64)
		buffer[i++] = '\0';
	if (ctx->projection_type == PROJECTION_ISOMETRIC)
		ft_strlcpy(buffer, "Projection: Isometric", 64);
	else if (ctx->projection_type == PROJECTION_CABINET)
		ft_strlcpy(buffer, "Projection: Cabinet", 64);
	else if (ctx->projection_type == PROJECTION_CONIC)
		ft_strlcpy(buffer, "Projection: Conic", 64);
	else
		ft_strlcpy(buffer, "Projection: Unknown", 64);
	put_debug_text(ctx, buffer, y_pos);
}

/**
 * @brief Display all LOD debug information
 *
 * @param ctx Context
 */
void	render_lod_debug(t_ctx *ctx)
{
	put_lod_level(ctx, ctx->lod_level, 40);
	put_map_size(ctx, 60);
	put_scale(ctx, 80);
	put_projection_type(ctx, 100);
}
