/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:23:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 09:18:06 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Attach mlx hooks to the window
 *
 * @param	ctx	Application context
 */
void	register_hooks(t_app *ctx)
{
	mlx_loop_hook(ctx->mlx, render_next_frame, ctx);
	mlx_hook(ctx->win, 2, 1L << 0, (int (*)())key_hook, ctx);
	mlx_hook(ctx->win, 17, 0, (int (*)())app_clear_0, ctx);
}
