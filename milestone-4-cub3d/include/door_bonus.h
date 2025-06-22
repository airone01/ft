/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:24:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 13:32:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_BONUS_H
# define DOOR_BONUS_H

# include "cub3d.h"

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/*
** i_system.c
*/

/**
 * @brief Finds the door at coords
 *
 * @param data App data
 * @param x X coordinate
 * @param y Y coordinate
 * @returns t_door* Door
 * @note This cannot be in cub3d_bonus.h because we need it for mandatory
 * compilation
 */
t_door	*get_door_at(t_data *data, int x, int y);

/**
 * @brief Initializes memory for the door system
 *
 * @param data App data
 */
void	init_door_system(t_data *data);

/**
 * @brief Checks if a door can be passed at the moment
 * @param data App data
 * @param x X coordinate of the door
 * @param y Y coordinate of the door
 * @returns bool Result
 */
bool	is_door_passable(t_data *data, int x, int y);

/**
 * @brief Toggles a door opened/closed
 * @param data App data
 * @param x X coordinate of the door
 * @param y Y coordinate of the door
 */
void	toggle_door(t_data *data, int x, int y);

/**
 * @brief Updates the door animation
 * @param data App data
 */
void	update_door_animations(t_data *data);

#endif // !DOOR_BONUS_H
