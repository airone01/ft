/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_horizontal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:33:39 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 14:12:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include <math.h>

static void	calculate_horizontal_steps(double angle, double *step_x,
		double *step_y)
{
	if (sin(angle) > 0.0)
	{
		*step_y = -1.0;
		*step_x = 1.0 / tan(angle);
	}
	else
	{
		*step_y = 1.0;
		*step_x = -1.0 / tan(angle);
	}
}

static void	set_initial_horizontal_pos(t_data *data, t_ray *ray, double angle)
{
	double	player_x;
	double	player_y;

	player_x = data->player.pos_x;
	player_y = data->player.pos_y;
	if (sin(angle) > 0.0)
		ray->horizontal_y = floor(player_y) - 0.000001;
	else
		ray->horizontal_y = floor(player_y) + 1.0;
	ray->horizontal_x = player_x + (player_y - ray->horizontal_y) / tan(angle);
}

static void	step_until_horizontal_wall(t_data *data, t_ray *ray, double step_x,
		double step_y)
{
	int	map_x;
	int	map_y;
	int	safety;

	safety = 0;
	map_x = (int)floor(ray->horizontal_x);
	map_y = (int)floor(ray->horizontal_y);
	while (safety < 1000 && is_valid_and_walkable(data, map_x, map_y))
	{
		ray->horizontal_x += step_x;
		ray->horizontal_y += step_y;
		map_x = (int)floor(ray->horizontal_x);
		map_y = (int)floor(ray->horizontal_y);
		safety++;
	}
}

void	find_horizontal_intersection(t_data *data, t_ray *ray)
{
	double	step_x;
	double	step_y;
	double	angle;

	angle = atan2(ray->ray_dir_y, ray->ray_dir_x);
	if (fabs(sin(angle)) < 0.000001)
	{
		ray->horizontal_x = DBL_MAX;
		ray->horizontal_dist = DBL_MAX;
		return ;
	}
	calculate_horizontal_steps(angle, &step_x, &step_y);
	set_initial_horizontal_pos(data, ray, angle);
	step_until_horizontal_wall(data, ray, step_x, step_y);
}
