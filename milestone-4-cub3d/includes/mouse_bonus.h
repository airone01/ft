/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:11:25 by maximart          #+#    #+#             */
/*   Updated: 2025/06/17 13:42:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_BONUS_H
# define MOUSE_BONUS_H

# include "cub3d.h"

/*******************************************************************************
 *                                    Macros                                   *
 ******************************************************************************/

# define MOUSE_SENSITIVITY 0.001
# define MOUSE_MIN 0.0005
# define MOUSE_MAX 0.005
# define MOUSE_LEFT_CLICK 1
# define MOUSE_RIGHT_CLICK 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

/*******************************************************************************
 *                                  Structures                                 *
 ******************************************************************************/

typedef struct s_mouse
{
	int		x;
	int		y;
	int		last_x;
	int		last_y;
	bool	is_active;
	bool	first_move;
	double	sensitivity;
}	t_mouse;

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/*
** o_buttons.c
*/

/**
 * @brief Handle mouse scroll wheel events
 *
 * @param button Mouse button code (MOUSE_SCROLL_UP/DOWN)
 */
void	handle_scroll_wheel(int button);

/**
 * @brief Process mouse button press events
 *
 * @param button Mouse button identifier
 * @return 0 on success
 */
int		mouse_press_handler(int button);

/*
** o_init.c
*/

/**
 * @brief Initialize mouse system with window dimensions
 *
 * @param win_width Window width in pixels
 * @param win_height Window height in pixels
 */
void	mouse_init(int win_width, int win_height);

/**
 * @brief Get pointer to global mouse state
 *
 * @return Pointer to global mouse structure
 */
t_mouse	*mouse_get_state(void);

/**
 * @brief Toggle mouse activation state
 */
void	mouse_toggle(void);

/**
 * @brief Setup MLX mouse event hooks
 *
 * @param data Main game data structure
 */
void	mouse_setup_hooks(t_data *data);

/*
** o_mouse.c
*/

/**
 * @brief Handle mouse movement events and camera rotation
 *
 * @param x Current mouse X coordinate
 * @param y Current mouse Y coordinate
 * @param data Main game data structure
 * @return 0 on success
 */
int		mouse_move_handler(int x, int y, t_data *data);

#endif // !MOUSE_BONUS_H
