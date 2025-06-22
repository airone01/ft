/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:22:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:56:25 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "cub3d.h"

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

bool		check_text_duplicate(t_data *data, const char *cardinal,
				char *exist);

/**
 * @brief Get RGB color from image data at a specific screen position
 *
 * @param texture Pointer to texture struct
 * @param x X screen coordinate
 * @param y Y screen coordinate
 * @return t_color Pixel color
 */
t_color		get_pixel_color(t_texture *texture, int x, int y);

/**
 * @brief Determine which texture to use based on wall orientation
 *
 * @param data App data for the bonus part
 * @param textures Pointer to textures struct
 * @param ray Pointer to ray
 * @return t_texture* Pointer to a newly initialized texture object
 */
t_texture	*get_wall_texture(t_data *data, t_textures *textures, t_ray *ray);

/**
 * @brief Load textures needed for cub3d from XPM texture files paths
 *
 * @param textures Pointer to textures struct
 * @param mlx_ptr Pointer to MLX struct
 * @param paths Each path to each cardinal direction texture
 * @return bool Whether the function succeeded or not
 *
 * @note Values in `paths` are stored in the crescent order of azimuth (or
 *       clockwise hortizontal angle), meaing N, E, S, W.
 * @see https://en.wikipedia.org/wiki/Cardinal_direction
 */
bool		load_textures(t_textures *textures, void *mlx_ptr, char *paths[4]);

/**
 * @brief Loads bonus textures only
 *
 * @param data App data
 * @param door_path Door path
 * @returns bool Whether it failed or not
 */
bool		load_bonus_textures(t_data *data, char *door_path);

bool		parse_texture_no_so(t_data *data, char *path, const char *cardinal);
bool		parse_texture_we_ea(t_data *data, char *path, const char *cardinal);

/**
 * @brief Resolves paths of textures
 *
 * @param data App data
 * @param map_path Map path
 */
char		**resolve_texture_paths(t_data *data, const char *map_path);

#endif // !TEXTURE_H