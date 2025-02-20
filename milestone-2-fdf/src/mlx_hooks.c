/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:23:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/20 14:55:01 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static int	app_clear_0(t_app *app)
{
	app_clear(app);
	exit(0);
}

static int	key_hook(int keycode, t_app *app)
{
	if (keycode == ESCAPE)
		app_clear_0(app);
	else if (keycode == ARROW_UP)
		app->offset_y -= 10;
	else if (keycode == ARROW_DOWN)
		app->offset_y += 10;
	else if (keycode == ARROW_LEFT)
		app->offset_x -= 10;
	else if (keycode == ARROW_RIGHT)
		app->offset_x += 10;
	else if (keycode == PLUS)
		app->scale *= 1.1;
	else if (keycode == MINUS)
		app->scale *= 0.9;
	else if (keycode == SQUARE_BRACKET_CLOSING)
		app->z_scale *= 1.1;
	else if (keycode == SQUARE_BRACKET_OPENING)
		app->z_scale *= 0.9;
	return (0);
}

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
