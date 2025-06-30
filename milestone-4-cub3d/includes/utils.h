/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:37:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 12:12:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/*
** u_path.c
*/

/**
 * @brief Resolve a relative path based on a reference file path
 *
 * @param base_path Path to the reference file (e.g., .cub file)
 * @param relative_path Relative path to resolve
 * @return char* Resolved absolute path, or NULL on failure
 */
char		*resolve_path(const char *base_path, const char *relative_path);

/*
** u_texture.c
*/

/**
 * @brief Load all game textures from parsed paths
 *
 * @param data App data containing texture paths
 * @return true On error
 * @return false On success
 */
bool		load_game_textures(t_data *data);
bool		load_game_textures_bonus(t_data *data);

/**
 * @brief Returns the map characters
 *
 * @returns The map characters
 */
const char	*map_chars(void);

#endif // !UTILS_H
