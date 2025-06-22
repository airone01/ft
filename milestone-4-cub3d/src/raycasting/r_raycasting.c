/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_raycasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:59:32 by maximart          #+#    #+#             */
/*   Updated: 2025/06/20 19:38:44 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"
#include "raycasting.h"
#include <math.h>

static double	calculate_distance(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

static void	set_horizontal_distance(t_data *data, t_ray *ray)
{
	double	player_x;
	double	player_y;

	player_x = data->player.pos_x;
	player_y = data->player.pos_y;
	if (ray->horizontal_x != DBL_MAX)
		ray->horizontal_dist = calculate_distance(player_x, player_y,
				ray->horizontal_x, ray->horizontal_y);
	else
		ray->horizontal_dist = DBL_MAX;
}

static void	set_vertical_distance(t_data *data, t_ray *ray)
{
	double	player_x;
	double	player_y;

	player_x = data->player.pos_x;
	player_y = data->player.pos_y;
	if (ray->vertical_y != DBL_MAX)
		ray->vertical_dist = calculate_distance(player_x, player_y,
				ray->vertical_x, ray->vertical_y);
	else
		ray->vertical_dist = DBL_MAX;
}

void	calculate_final_distance(t_data *data, t_ray *ray)
{
	double	player_angle;
	double	ray_angle;
	double	correction;

	set_horizontal_distance(data, ray);
	set_vertical_distance(data, ray);
	if (ray->vertical_dist < ray->horizontal_dist)
	{
		ray->perp_wall_dist = ray->vertical_dist;
		ray->side = SIDE_EAST_WEST;
	}
	else
	{
		ray->perp_wall_dist = ray->horizontal_dist;
		ray->side = SIDE_NORTH_SHOUTH;
	}
	ray_angle = atan2(ray->ray_dir_y, ray->ray_dir_x);
	player_angle = atan2(data->player.dir_y, data->player.dir_x);
	correction = cos(ray_angle - player_angle);
	ray->perp_wall_dist *= correction;
}

void	grid_raycasting(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < data->win_width)
	{
		cast_grid_ray(data, &ray, x);
		data->z_buffer[x] = ray.perp_wall_dist;
		draw_ceiling(data, x, ray.draw_start, data->ceil_color);
		draw_textured_line(data, &ray, x);
		draw_floor(data, x, ray.draw_end, data->floor_color);
		x++;
	}
}
