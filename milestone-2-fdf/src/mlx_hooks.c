/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:23:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/06 13:46:00 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook_int(int keycode, t_app *ctx)
{
	key_hook(keycode, ctx);
	return (0);
}

int	app_clear_0_int(t_app *ctx)
{
	app_clear_0(ctx);
	return (0);
}

/**
 * @brief	Attach mlx hooks to the window
 *
 * @param	ctx	Application context
 */
void	register_hooks(t_app *ctx)
{
	mlx_loop_hook(ctx->mlx, render_next_frame, ctx);
	mlx_hook(ctx->win, 2, 1L << 0, key_hook_int, ctx);
	mlx_hook(ctx->win, 17, 0, app_clear_0_int, ctx);
}
