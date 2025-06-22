/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:01:13 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 14:36:52 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door_bonus.h"
#include "mouse_bonus.h"
#include "pproc.h"
#include "sprite_bonus.h"

void	handle_main_bonus_features(t_data *data)
{
	mouse_init(data->win_width, data->win_height);
	init_sprite_system(data);
	init_door_system(data);
}
