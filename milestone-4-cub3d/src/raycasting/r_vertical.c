/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_vertical.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:33:47 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 14:15:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include <math.h>

static void	calculate_vertical_steps(double angle, double *step_x,
		double *step_y)
{
	if (cos(angle) < 0.0)
	{
		*step_x = -1.0;
		*step_y = 1.0 * tan(angle);
	}
	else
	{
		*step_x = 1.0;
		*step_y = -1.0 * tan(angle);
	}
}

static void	set_initial_vertical_pos(t_data *data, t_ray *ray, double angle)
{
	double	player_x;
	double	player_y;

	player_x = data->player.pos_x;
	player_y = data->player.pos_y;
	if (cos(angle) < 0.0)
		ray->vertical_x = floor(player_x) - 0.000001;
	else
		ray->vertical_x = floor(player_x) + 1.0;
	ray->vertical_y = player_y + (player_x - ray->vertical_x) * tan(angle);
}

static void	step_until_vertical_wall(t_data *data, t_ray *ray, double step_x,
		double step_y)
{
	int	map_x;
	int	map_y;
	int	safety;

	safety = 0;
	map_x = (int)floor(ray->vertical_x);
	map_y = (int)floor(ray->vertical_y);
	while (safety < 1000 && is_valid_and_walkable(data, map_x, map_y))
	{
		ray->vertical_x += step_x;
		ray->vertical_y += step_y;
		map_x = (int)floor(ray->vertical_x);
		map_y = (int)floor(ray->vertical_y);
		safety++;
	}
}

void	find_vertical_intersection(t_data *data, t_ray *ray)
{
	double	step_x;
	double	step_y;
	double	angle;

	angle = atan2(ray->ray_dir_y, ray->ray_dir_x);
	if (fabs(cos(angle)) < 0.000001)
	{
		ray->vertical_y = DBL_MAX;
		ray->vertical_dist = DBL_MAX;
		return ;
	}
	calculate_vertical_steps(angle, &step_x, &step_y);
	set_initial_vertical_pos(data, ray, angle);
	step_until_vertical_wall(data, ray, step_x, step_y);
}
