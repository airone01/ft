/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:23:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/20 20:53:40 by elagouch         ###   ########.fr       */
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
	if (keycode == KEY_ESCAPE || keycode == KEY_Q)
		app_clear_0(app);
	else if (keycode == KEY_W || keycode == KEY_ARROW_UP)
	{
		app->offset_y -= 10;
		app->needs_render = true;
	}
	else if (keycode == KEY_S || keycode == KEY_ARROW_DOWN)
	{
		app->offset_y += 10;
		app->needs_render = true;
	}
	else if (keycode == KEY_A || keycode == KEY_ARROW_LEFT)
	{
		app->offset_x -= 10;
		app->needs_render = true;
	}
	else if (keycode == KEY_D || keycode == KEY_ARROW_RIGHT)
	{
		app->offset_x += 10;
		app->needs_render = true;
	}
	else if (keycode == KEY_EQUALS || keycode == KEY_NUMPAD_PLUS)
	{
		app->scale *= 1.1;
		app->needs_render = true;
	}
	else if (keycode == KEY_DASH || keycode == KEY_NUMPAD_MINUS)
	{
		app->scale *= 0.9;
		app->needs_render = true;
	}
	else if (keycode == KEY_SQUARE_BRACKET_CLOSING)
	{
		app->z_scale *= 1.1;
		app->needs_render = true;
	}
	else if (keycode == KEY_SQUARE_BRACKET_OPENING)
	{
		app->z_scale *= 0.9;
		app->needs_render = true;
	}
	else if (keycode == KEY_1)
	{
		app->color_scheme = (app->color_scheme + 1) % 4;
		app->needs_render = true;
	}
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
