/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_mouse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:47:37 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 13:43:45 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mouse_bonus.h"
#include <math.h>
#include <stdlib.h>

static void	mouse_recenter(t_data *data)
{
	t_mouse	*mouse;
	int		center_x;
	int		center_y;

	mouse = mouse_get_state();
	if (!mouse->is_active)
	{
		mlx_mouse_show(data->mlx, data->win);
		return ;
	}
	else
		mlx_mouse_hide(data->mlx, data->win);
	center_x = (int)(data->win_width * 0.5);
	center_y = (int)(data->win_height * 0.5);
	mlx_mouse_move(data->mlx, data->win, center_x, center_y);
	mouse->last_x = center_x;
	mouse->last_y = center_y;
}

static double	mouse_get_delta(int current_x, int current_y)
{
	t_mouse	*mouse;
	double	delta_x;

	mouse = mouse_get_state();
	if (!mouse->is_active)
		return (0.0);
	if (mouse->first_move)
	{
		mouse->last_x = current_x;
		mouse->last_y = current_y;
		mouse->first_move = false;
		return (0.0);
	}
	delta_x = (double)(mouse->last_x - current_x) * mouse->sensitivity;
	mouse->last_x = current_x;
	mouse->last_y = current_y;
	return (delta_x);
}

static void	mouse_rotate_camera(t_player *player, double delta_x)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(delta_x);
	sin_angle = sin(delta_x);
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos_angle - player->dir_y * sin_angle;
	player->dir_y = old_dir_x * sin_angle + player->dir_y * cos_angle;
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
	player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;
}

int	mouse_move_handler(int x, int y, t_data *data)
{
	double	delta_x;
	int		center_x;
	int		center_y;

	center_x = (int)(data->win_width * 0.5);
	center_y = (int)(data->win_height * 0.5);
	delta_x = mouse_get_delta(x, y);
	if (delta_x != 0.0)
		mouse_rotate_camera(&data->player, delta_x);
	if (abs(x - center_x) > 50 || abs(y - center_y) > 50)
		mouse_recenter(data);
	return (0);
}
