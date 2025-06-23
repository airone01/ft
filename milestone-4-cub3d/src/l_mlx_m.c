/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_mlx_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:48:31 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/17 19:13:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"
#include "mlx.h"
#include "player.h"

void	handle_mlx_bonus_features(t_data *data, int keycode)
{
	(void)data;
	(void)keycode;
}

void	setup_mlx_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, (int (*)())render_frame, data);
	mlx_hook(data->win, ON_DESTROY, 0, (int (*)())hook_destroy, data);
	mlx_hook(data->win, ON_KEYDOWN, 1L << 0, key_press, data);
	mlx_hook(data->win, ON_KEYUP, 1L << 1, key_release, data);
}
