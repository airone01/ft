/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_mlx_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:16:42 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 13:44:39 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door_bonus.h"
#include "draw.h"
#include "libft.h"
#include "mlx.h"
#include "mouse_bonus.h"
#include "player.h"

void	handle_mlx_bonus_features_loop(struct s_double_int player, t_data *data)
{
	int	dx;
	int	dy;
	int	check_x;
	int	check_y;

	dy = -2;
	while (++dy <= 1)
	{
		dx = -2;
		while (++dx <= 1)
		{
			check_x = *player.x + dx;
			check_y = *player.y + dy;
			if (check_x >= 0 && check_x < data->map_width && check_y >= 0
				&& check_y < data->map_height && data->map[check_y]
				&& check_x < (int)ft_strlen(data->map[check_y])
				&& data->map[check_y][check_x] == 'D')
			{
				toggle_door(data, check_x, check_y);
				return ;
			}
		}
	}
}

void	handle_mlx_bonus_features(t_data *data, int keycode)
{
	double	check_dist;
	int		frnt_x;
	int		frnt_y;
	int		pl_x;
	int		pl_y;

	if (keycode == LMB)
		mouse_toggle();
	else if (keycode == SPACE)
	{
		check_dist = 1.8;
		frnt_x = (int)(data->player.pos_x + data->player.dir_x * check_dist);
		frnt_y = (int)(data->player.pos_y - data->player.dir_y * check_dist);
		if (frnt_x >= 0 && frnt_x < data->map_width && frnt_y >= 0
			&& frnt_y < data->map_height && data->map[frnt_y]
			&& frnt_x < (int)ft_strlen(data->map[frnt_y])
			&& data->map[frnt_y][frnt_x] == 'D')
		{
			toggle_door(data, frnt_x, frnt_y);
			return ;
		}
		pl_x = (int)data->player.pos_x;
		pl_y = (int)data->player.pos_y;
		handle_mlx_bonus_features_loop((t_double_int){&pl_x, &pl_y}, data);
	}
}

void	setup_mlx_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, (int (*)())render_frame, data);
	mlx_hook(data->win, ON_DESTROY, 0, (int (*)())hook_destroy, data);
	mlx_hook(data->win, ON_KEYDOWN, 1L << 0, key_press, data);
	mlx_hook(data->win, ON_KEYUP, 1L << 1, key_release, data);
	mouse_setup_hooks(data);
}
