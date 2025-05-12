/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:23:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:23:12 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook_int(int keycode, t_ctx *ctx)
{
	key_hook(keycode, ctx);
	return (0);
}

int	ctx_clear_0_int(t_ctx *ctx)
{
	ctx_clear_0(ctx);
	return (0);
}

/**
 * @brief	Attach mlx hooks to the window
 *
 * @param	ctx	Context
 */
void	register_hooks(t_ctx *ctx)
{
	mlx_loop_hook(ctx->mlx, render_next_frame, ctx);
	mlx_hook(ctx->win, 2, 1L << 0, key_hook_int, ctx);
	mlx_hook(ctx->win, 17, 0, ctx_clear_0_int, ctx);
}
