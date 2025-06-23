/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_math.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:04:42 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 13:36:55 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include <math.h>

double	calculate_wall_hit(t_data *data, t_ray *ray)
{
	double	wall_x;

	(void)data;
	if (ray->side == SIDE_EAST_WEST)
		wall_x = ray->vertical_y;
	else
		wall_x = ray->horizontal_x;
	wall_x -= floor(wall_x);
	if (wall_x < 0)
		wall_x = 0;
	if (wall_x >= 1.0)
		wall_x = 0.999;
	return (wall_x);
}

int	calculate_texture_x(double wall_x, t_texture *texture, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == SIDE_EAST_WEST && ray->ray_dir_x < 0)
		|| (ray->side == SIDE_NORTH_SHOUTH && ray->ray_dir_y > 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}
