/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_extra.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:28:33 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 13:32:58 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPS_EXTRA_H
# define FPS_EXTRA_H

# include "cub3d.h"

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/**
 * @brief Display FPS counter on screen
 *
 * @param data Main data structure
 */
void	display_fps(t_data *data);

/**
 * @brief Update FPS counter
 *
 * @param data Main data structure
 */
void	update_fps_counter(t_data *data);

#endif // !FPS_EXTRA_H
