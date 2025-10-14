/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:36:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/17 14:24:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

/*******************************************************************************
 *                                  Structures                                 *
 ******************************************************************************/

/*
** For some unknown reason, the MLX only defines ON_DESTROY
*/
enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	// ON_DESTROY = 17
};

typedef enum e_keyboard
{
	ESCAPE = 65307,
	W = 119,
	S = 115,
	A = 97,
	D = 100,
	LEFT_ARROW = 65361,
	RIGHT_ARROW = 65363,
	SPACE = 32,
	LMB = 1,
}		t_keyboard;

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/*
** l_init.c
*/

/**
 * @brief Initializes the player structure from app state
 *
 * @param data App state
 *
 * @note There are no checks for empty data struct, so passing a NULL *will*
 *       segfault.
 */
void	init_player(t_data *data);

/*
** l_mov.c
*/

/**
 * @brief Move the player
 * Bases itself on the current control state and collision detection.
 *
 * @param data App data
 * @param player Player
 * @param map Map
 *
 * @see Comments in `player_move.c`, they give context for the collision
 *      detection system.
 */
void	move_player(t_data *data, t_player *player, char **map);

/*
** l_mlx_{m,b}.c
*/

/**
 * @brief Set the up mlx hooks
 *
 * @param data App data
 */
void	setup_mlx_hooks(t_data *data);

/*
** l_mlx.c
*/

/*
** MLX hook on key press
*/
int		key_press(int keycode, t_data *data);
/*
** MLX hook on key release
*/
int		key_release(int keycode, t_data *data);
/*
** MLX hook on app destroy
*/
void	hook_destroy(t_data *data);

#endif // !PLAYER_H
