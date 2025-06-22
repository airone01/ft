/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:57:52 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:54:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file is named `mem.h` because there already is a `memory.h` in the\
** standard lib.
*/

#ifndef MEM_H
# define MEM_H

# include "cub3d.h"

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/**
 * @brief Frees the door system, duh.
 *
 * @param data App data
 */
void	free_door_system(t_data *data);

/**
 * @brief Final clearing function
 *
 * @param data Pointer to data to be cleared
 * @return void New value for parameter
 */
void	*free_resources(t_data **data);

/**
 * @brief Frees the map
 *
 * @param data Cub3d map
 */
void	free_map(t_data *data);

/**
 * @brief Frees the map copy
 *
 * @param map_copy Cub3d map copy
 * @param height Cub3d map height
 */
void	free_map_copy(char **map_copy, int height);

/**
 * @brief init the map in a buffer before in the data
 *
 * @param data Cub3d map
 */
bool	init_map_buffer(t_map_buffer *buffer);

#endif // !MEM_H