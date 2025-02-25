/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_lod_debug.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:13:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 12:49:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Prepare and display LOD level text
 *
 * @param ctx Application context
 * @param lod Current LOD level
 * @param y_pos Vertical position for the text
 */
static void	put_lod_level(t_app *ctx, int lod, int y_pos)
{
	char	buffer[64];
	int		i;

	i = 0;
	while (i < 64)
		buffer[i++] = '\0';
	ft_strlcpy(buffer, "LOD Level: ", 64);
	i = (int)ft_strlen(buffer);
	append_int(buffer + i, lod, 64 - i);
	put_debug_text(ctx, buffer, y_pos);
}

/**
 * @brief Prepare and display map dimensions
 *
 * @param ctx Application context
 * @param y_pos Vertical position for the text
 */
static void	put_map_size(t_app *ctx, int y_pos)
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
 * @param ctx Application context
 * @param y_pos Vertical position for the text
 */
static void	put_scale(t_app *ctx, int y_pos)
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
 * @brief Prepare and display auto LOD status
 *
 * @param ctx Application context
 * @param is_on Whether auto LOD is enabled
 * @param y_pos Vertical position for the text
 */
static void	put_auto_lod(t_app *ctx, t_bool is_on, int y_pos)
{
	char	buffer[64];

	ft_strlcpy(buffer, "Auto LOD: ", 64);
	if (is_on)
		ft_strlcat(buffer, "ON", 64);
	else
		ft_strlcat(buffer, "OFF", 64);
	put_debug_text(ctx, buffer, y_pos);
}

/**
 * @brief Display LOD information overlay on screen
 *
 * @param ctx Application context
 */
void	render_lod_debug(t_app *ctx)
{
	int		lod;
	t_bool	is_auto_lod;

	lod = ctx->lod_level;
	if (lod == 0)
		lod = get_appropriate_lod(ctx);
	is_auto_lod = (ctx->lod_level == 0);
	put_lod_level(ctx, lod, 40);
	put_map_size(ctx, 60);
	put_scale(ctx, 80);
	put_auto_lod(ctx, is_auto_lod, 100);
}
