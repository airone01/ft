/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:23:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 21:13:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Attach mlx hooks to the window
 *
 * @param	app	Application context
 */
void	register_hooks(t_app *app)
{
	mlx_loop_hook(app->mlx, render_next_frame, app);
	mlx_hook(app->win, 2, 1L << 0, key_hook, app);
	mlx_hook(app->win, 17, 0, app_clear_0, app);
}
