/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:38:33 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 13:41:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door_bonus.h"
#include "libft.h"
#include "raycasting.h"

void	init_ray(t_ray *ray, t_player *player, double camera_x)
{
	ray->ray_dir_x = player->dir_x - player->plane_x * camera_x;
	ray->ray_dir_y = player->dir_y - player->plane_y * camera_x;
	ray->hit = 0;
}

void	cast_grid_ray(t_data *data, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)data->win_width - 1;
	init_ray(ray, &data->player, camera_x);
	find_horizontal_intersection(data, ray);
	find_vertical_intersection(data, ray);
	calculate_final_distance(data, ray);
	calculate_line_height(ray, data->win_height);
}

void	calculate_line_height(t_ray *ray, int screen_height)
{
	ray->line_height = (int)(screen_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + screen_height / 2;
	if (ray->draw_end >= screen_height)
		ray->draw_end = screen_height - 1;
}

bool	is_valid_and_walkable(t_data *data, int x, int y)
{
	t_door	*door;

	if (y < 0 || y >= data->map_height)
		return (false);
	if (x < 0 || x >= data->map_width)
		return (false);
	if (!data->map[y])
		return (false);
	if (x >= (int)ft_strlen(data->map[y]))
		return (false);
	if (data->map[y][x] == 'D')
	{
		door = get_door_at(data, x, y);
		if (door && door->prog >= 1.0f)
			return (true);
		return (false);
	}
	return (!ft_strchr("1", data->map[y][x]));
}
