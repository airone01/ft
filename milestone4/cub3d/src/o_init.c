/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:49:58 by maximart          #+#    #+#             */
/*   Updated: 2025/06/03 14:12:52 by maximart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mouse_bonus.h"

static t_mouse	g_mouse;

void	mouse_init(int win_width, int win_height)
{
	g_mouse.x = (int)(win_width * 0.5);
	g_mouse.y = (int)(win_height * 0.5);
	g_mouse.last_x = g_mouse.x;
	g_mouse.last_y = g_mouse.y;
	g_mouse.is_active = false;
	g_mouse.first_move = true;
	g_mouse.sensitivity = MOUSE_SENSITIVITY;
}

t_mouse	*mouse_get_state(void)
{
	return (&g_mouse);
}

void	mouse_toggle(void)
{
	g_mouse.is_active = !g_mouse.is_active;
	if (g_mouse.is_active)
		g_mouse.first_move = true;
}

void	mouse_setup_hooks(t_data *data)
{
	mlx_hook(data->win, 6, 1L << 6, mouse_move_handler, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_press_handler, data);
}
