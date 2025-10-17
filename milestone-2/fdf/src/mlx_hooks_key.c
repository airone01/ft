/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:52:43 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:19:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	key_resets_render(int keycode)
{
	return (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D || keycode == KEY_ARROW_UP
		|| keycode == KEY_ARROW_DOWN || keycode == KEY_ARROW_LEFT
		|| keycode == KEY_ARROW_RIGHT || keycode == KEY_EQUALS
		|| keycode == KEY_NUMPAD_PLUS || keycode == KEY_DASH
		|| keycode == KEY_NUMPAD_MINUS || keycode == KEY_SQUARE_BRACKET_CLOSING
		|| keycode == KEY_SQUARE_BRACKET_OPENING || keycode == KEY_1
		|| keycode == KEY_ESCAPE || keycode == KEY_Q || keycode == KEY_E
		|| keycode == KEY_R || keycode == KEY_F || keycode == KEY_T
		|| keycode == KEY_G || keycode == KEY_F1 || keycode == KEY_F2
		|| keycode == KEY_F3 || keycode == KEY_F4 || keycode == KEY_P
		|| keycode == KEY_9 || keycode == KEY_0);
}

static void	key_hook3(int keycode, t_ctx *ctx)
{
	if (keycode == KEY_F6)
		toggle_debug_mode(ctx, DEBUG_SECTIONS);
	else if (keycode == KEY_F7)
		toggle_debug_mode(ctx, DEBUG_LOD);
	else if (keycode == KEY_9)
		ctx->horizon_distance *= 1.1;
	else if (keycode == KEY_0)
		ctx->horizon_distance *= 0.9;
}

void	key_hook2(int keycode, t_ctx *ctx)
{
	if (keycode == KEY_Q)
		ctx->rot_x += 0.1;
	else if (keycode == KEY_E)
		ctx->rot_x -= 0.1;
	else if (keycode == KEY_R)
		ctx->rot_y += 0.1;
	else if (keycode == KEY_F)
		ctx->rot_y -= 0.1;
	else if (keycode == KEY_T)
		ctx->rot_z += 0.1;
	else if (keycode == KEY_G)
		ctx->rot_z -= 0.1;
	else if (keycode == KEY_F1)
		ctx->lod_level = LOD_VERY_LOW;
	else if (keycode == KEY_F2)
		ctx->lod_level = LOD_LOW;
	else if (keycode == KEY_F3)
		ctx->lod_level = LOD_MEDIUM;
	else if (keycode == KEY_F4)
		ctx->lod_level = LOD_HIGH;
	else if (keycode == KEY_P)
		ctx->projection_type = (ctx->projection_type + 1) % 3;
	else
		key_hook3(keycode, ctx);
}

/**
 * @brief Main hook for when key is pressed
 *
 * @param keycode Key
 * @param ctx Context
 */
void	key_hook(int keycode, t_ctx *ctx)
{
	if (key_resets_render(keycode))
		ctx->needs_render = true;
	if (keycode == KEY_ESCAPE)
		ctx_clear_0(ctx);
	else if (keycode == KEY_W || keycode == KEY_ARROW_UP)
		ctx->offset_y -= 10;
	else if (keycode == KEY_S || keycode == KEY_ARROW_DOWN)
		ctx->offset_y += 10;
	else if (keycode == KEY_A || keycode == KEY_ARROW_LEFT)
		ctx->offset_x -= 10;
	else if (keycode == KEY_D || keycode == KEY_ARROW_RIGHT)
		ctx->offset_x += 10;
	else if (keycode == KEY_EQUALS || keycode == KEY_NUMPAD_PLUS)
		ctx->scale *= 1.1;
	else if (keycode == KEY_DASH || keycode == KEY_NUMPAD_MINUS)
		ctx->scale *= 0.9;
	else if (keycode == KEY_SQUARE_BRACKET_CLOSING)
		ctx->z_scale *= 1.1;
	else if (keycode == KEY_SQUARE_BRACKET_OPENING)
		ctx->z_scale *= 0.9;
	else if (keycode == KEY_1)
		ctx->color_scheme = (ctx->color_scheme + 1) % 4;
	else
		key_hook2(keycode, ctx);
}
