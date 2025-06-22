/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_render_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:35:40 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:25:03 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door_bonus.h"
#include "minimap_bonus.h"
#include "sprite_bonus.h"

void	handle_render_bonus_features(t_data *data)
{
	draw_minimap(data);
	update_door_animations(data);
	update_sprite_animations(data);
}

void	handle_render_extra_features(t_data *data)
{
	(void)data;
}
