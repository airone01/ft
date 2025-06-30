/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:31:07 by maximart          #+#    #+#             */
/*   Updated: 2025/06/17 14:02:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H

# include "cub3d.h"

/*******************************************************************************
 *                                    Macros                                   *
 ******************************************************************************/

# define MINIMAP_SIZE 150
# define MINIMAP_MARGIN 40
# define MINIMAP_SCALE 15
# define MINIMAP_PLAYER_SIZE 3
# define MINIMAP_FOV_LENGTH 200
# define MINIMAP_WALL_COLOR 0xFFFFFF
# define MINIMAP_PLAYER_COLOR 0xFF0000
# define MINIMAP_FOV_COLOR 0x00FF00
# define MINIMAP_BORDER_COLOR 0x808080

/*******************************************************************************
 *                                  Structures                                 *
 ******************************************************************************/

typedef struct s_draw_params
{
	int		player_screen[2];
	int		x;
	int		y;
	int		width;
	int		height;
	int		minimap_x;
	int		minimap_y;
	int		cell_size;
	int		center_x;
	int		center_y;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	t_color	color;
}	t_draw_params;

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/*
** n_minimap.c
*/

/**
 * @brief Draws the complete minimap on screen
 *
 * @param data Main game data structure containing player and map info
 */
void	draw_minimap(t_data *data);

/**
 * @brief Draws a filled rectangle with specified parameters
 *
 * @param data Main game data structure for screen dimensions
 * @param params Drawing parameters including position, size, and color
 */
void	draw_filled_rect(t_data *data, t_draw_params *params);

/*
** n_draw.c
*/

/**
 * @brief Clamps rectangle bounds to fit within screen dimensions
 *
 * @param data Main game data structure containing screen dimensions
 * @param params Drawing parameters to be clamped (modified in place)
 */
void	clamp_rect_bounds(t_data *data, t_draw_params *params);

/**
 * @brief Draws a line between two points using Bresenham's algorithm
 *
 * @param data Main game data structure for screen access
 * @param params Line parameters (start/end points and color)
 */
void	draw_line(t_data *data, t_draw_params *params);

/**
 * @brief Draws the border frame around the minimap
 *
 * @param data Main game data structure
 * @param params Drawing parameters for border positioning
 */
void	draw_minimap_border(t_data *data, t_draw_params *params);

/*
** n_draw_utils.c
*/

/**
 * @brief Draws the player's field of view cone on minimap
 *
 * @param data Main game data with player direction information
 * @param params Drawing parameters for FOV visualization
 * @param player_screen Array with player screen position [x, y]
 */
void	draw_player_fov(t_data *data, t_draw_params *params);

/**
 * @brief Draws the four borderlines around minimap perimeter
 *
 * @param data Main game data structure
 * @param params Drawing parameters with border positioning
 */
void	draw_border_lines(t_data *data, t_draw_params *params);

/*
** n_grid.c
*/

/**
 * @brief Renders the map grid/cells on the minimap
 *
 * @param data Main game data containing the map array
 * @param params Drawing parameters for grid positioning and scaling
 */
void	draw_minimap_grid(t_data *data, t_draw_params *params);

/*
** n_player.c
*/

/**
 * @brief Casts a single ray for field of view calculation
 *
 * @param data Main game data with player position and map
 * @param params Drawing parameters, end coordinates stored in end_x/end_y
 * @param angle Ray direction in radians
 */
void	cast_fov_ray(t_data *data, t_draw_params *params, double angle);

/**
 * @brief Draws the player representation on the minimap
 *
 * @param data Main game data with player information
 * @param params Drawing parameters for player visualization
 */
void	draw_minimap_player(t_data *data, t_draw_params *params);

/*
** n_utils.c
*/

/**
 * @brief Checks if screen coordinates are within minimap FOV bounds
 *
 * @param params Drawing parameters containing minimap boundaries
 * @param screen_x X coordinate to check
 * @param screen_y Y coordinate to check
 * @return true if coordinates are outside bounds, false if within
 */
bool	check_fov_bounds(t_draw_params *params, int screen_x, int screen_y);

/**
 * @brief Checks if player sprite fits within minimap boundaries
 *
 * @param params Drawing parameters with player position and minimap bounds
 * @return true if player fits within bounds, false otherwise
 */
bool	is_player_in_bounds(t_draw_params *params);

/**
 * @brief Validates pixel coordinates within screen boundaries
 *
 * @param data Main game data with player information
 * @param x Coordinate to validate
 * @param y Coordinate to validate
 * @return 1 if valid, 0 otherwise
 */
int		is_pixel_valid(t_data *data, int x, int y);

/**
 * @brief Calculates step directions for line drawing algorithms
 *
 * @param params Drawing parameters with player position and minimap bounds
 * @param step_x Pointer to store X direction (-1 or +1)
 * @param step_y Pointer to store Y direction (-1 or +1)
 */
void	init_steps(t_draw_params *params, int *step_x, int *step_y);

/**
 * @brief Initializes ray position and direction for raycasting
 *
 * @param data Pointer to data structure containing player position
 * @param angle Ray casting angle in radians
 * @param ray_pos Array to store ray starting position [x, y]
 * @param ray_dir Array to store ray direction vector [x, y]
 * @warning NULL pointers cause undefined behavior
 */
void	init_ray_pos(t_data *data, double angle, double *ray_pos,
			double *ray_dir);

#endif // !MINIMAP_BONUS_H
