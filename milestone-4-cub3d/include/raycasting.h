/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:40:53 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 13:31:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/*
** r_horizontal.c
*/

/**
 * @brief Finds the closes horizontal intersection of a ray
 *
 * @param data App data
 * @param ray Ray
 */
void	find_horizontal_intersection(t_data *data, t_ray *ray);

/*
** r_raycasting.c
*/

/**
 * @brief Caulates the final distance to a wall with ray (with correction)
 *
 * @param data App data
 * @param ray Ray
 *
 * @note Distance will be set in data->perp_wall_dist
 */
void	calculate_final_distance(t_data *data, t_ray *ray);

/**
 * @brief All of the raycasting process
 *
 * @param data App data
 * @param ray Ray
 */
void	grid_raycasting(t_data *data);

/*
** r_utils.c
*/

/*
** Inits a ray with simple math.
*/
void	init_ray(t_ray *ray, t_player *player, double camera_x);

/**
 * @brief Heavy work of the raycasting process.
 *
 * @param data App data
 * @param ray Ray
 * @param x X coordinate
 */
void	cast_grid_ray(t_data *data, t_ray *ray, int x);

/**
 * @brief Figures out a line height from the screen size
 *
 * @param ray Ray
 * @param screen_height Screen height
 */
void	calculate_line_height(t_ray *ray, int screen_height);

/**
 * @brief Checks if the cell should be considered a "blank space" (floor), or
 * anything solid.
 *
 * @param data App data
 * @param x X codinate
 * @param y Y codinate
 * @returns bool Whether the cell is "walkable"
 */
bool	is_valid_and_walkable(t_data *data, int x, int y);

/*
** r_vertical.c
*/

/**
 * @brief Find the closest vertical intersection with a ray
 *
 * @param data App data
 * @param ray Ray
 */
void	find_vertical_intersection(t_data *data, t_ray *ray);

#endif // !RAYCASTING_H
