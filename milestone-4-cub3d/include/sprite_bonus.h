/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:15:07 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:56:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_BONUS_H
# define SPRITE_BONUS_H

# include "cub3d.h"

/*******************************************************************************
 *                                  Structures                                 *
 ******************************************************************************/

typedef struct s_sprite_render
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}	t_sprite_render;

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/*
** j_system.c
*/

/**
 * @brief Initializes the sprite system
 *
 * @param data App data
 */
void		init_sprite_system(t_data *data);

/**
 * @brief Frees the sprite system
 *
 * @param data App data
 */
void		free_sprite_system(t_data *data);

/**
 * @brief Updates all sprite animations
 *
 * @param data App data
 */
void		update_sprite_animations(t_data *data);

/**
 * @brief Adds a sprite to the system
 *
 * @param data App data
 * @param x X position
 * @param y Y position
 * @return bool Success
 */
bool		add_sprite(t_data *data, double x, double y);

/*
** j_render.c
*/

/**
 * @brief Renders all sprites
 *
 * @param data App data
 */
void		render_sprites(t_data *data);

/**
 * @brief Sorts sprites by distance for proper rendering order
 *
 * @param data App data
 */
void		sort_sprites_by_distance(t_data *data);

/*
** j_animation.c
*/

/**
 * @brief Loads sprite textures for a given type
 *
 * @param data App data
 * @param sprite Sprite to load textures for
 * @return bool Success
 */
bool		load_sprite_textures(t_data *data, t_sprite *sprite);

/**
 * @brief Updates a single sprite animation
 *
 * @param sprite Sprite to update
 * @param delta_time Time since last frame
 */
void		update_sprite_animation(t_sprite *sprite, double delta_time);

/*
** j_utils.c
*/

/**
 * @brief Gets the current texture for a sprite
 *
 * @param sprite Sprite
 * @return t_texture* Current texture
 */
t_texture	*get_sprite_texture(t_sprite *sprite);

/**
 * @brief Checks if a sprite is visible from player position
 *
 * @param data App data
 * @param sprite Sprite to check
 * @return bool Visibility
 */
bool		is_sprite_visible(t_data *data, t_sprite *sprite);

#endif // !SPRITE_BONUS_H