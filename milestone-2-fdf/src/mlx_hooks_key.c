/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:52:43 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 21:06:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static t_bool	key_resets_render(int keycode)
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
		|| keycode == KEY_G);
}

static void	key_hook3(int keycode, t_app *app)
{
	(void)keycode;
	(void)app;
	return ;
}

void	key_hook2(int keycode, t_app *app)
{
	if (keycode == KEY_Q)
		app->rot_x += 0.1;
	else if (keycode == KEY_E)
		app->rot_x -= 0.1;
	else if (keycode == KEY_R)
		app->rot_y += 0.1;
	else if (keycode == KEY_F)
		app->rot_y -= 0.1;
	else if (keycode == KEY_T)
		app->rot_z += 0.1;
	else if (keycode == KEY_G)
		app->rot_z -= 0.1;
	else
		key_hook3(keycode, app);
}

int	key_hook(int keycode, t_app *app)
{
	if (key_resets_render(keycode))
		app->needs_render = true;
	if (keycode == KEY_ESCAPE)
		app_clear_0(app);
	else if (keycode == KEY_W || keycode == KEY_ARROW_UP)
		app->offset_y -= 10;
	else if (keycode == KEY_S || keycode == KEY_ARROW_DOWN)
		app->offset_y += 10;
	else if (keycode == KEY_A || keycode == KEY_ARROW_LEFT)
		app->offset_x -= 10;
	else if (keycode == KEY_D || keycode == KEY_ARROW_RIGHT)
		app->offset_x += 10;
	else if (keycode == KEY_EQUALS || keycode == KEY_NUMPAD_PLUS)
		app->scale *= 1.1;
	else if (keycode == KEY_DASH || keycode == KEY_NUMPAD_MINUS)
		app->scale *= 0.9;
	else if (keycode == KEY_SQUARE_BRACKET_CLOSING)
		app->z_scale *= 1.1;
	else if (keycode == KEY_SQUARE_BRACKET_OPENING)
		app->z_scale *= 0.9;
	else if (keycode == KEY_1)
		app->color_scheme = (app->color_scheme + 1) % 4;
	else
		key_hook2(keycode, app);
	return (0);
}
