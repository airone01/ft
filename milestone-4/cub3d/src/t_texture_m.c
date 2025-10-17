/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_texture_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:27:44 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 14:28:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

bool	load_bonus_textures(t_data *data, char *door_path)
{
	(void)data;
	(void)door_path;
	return (false);
}

t_texture	*get_wall_texture_bonus(t_data *data, t_textures *textures,
		t_ray *ray)
{
	(void)ray;
	(void)data;
	(void)textures;
	return (NULL);
}
