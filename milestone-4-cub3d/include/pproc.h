/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pproc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:37:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 13:33:25 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contains all the headers for the conditional preprocessor builds,
** for everything to link together good in the final app.
*/

#ifndef PPROC_H
# define PPROC_H

# include "cub3d.h"

/*
** Main file
*/
void	handle_main_bonus_features(t_data *data);

/*
** Rendering
*/
void	handle_render_bonus_features(t_data *data);
void	handle_render_extra_features(t_data *data);

/*
** MLX
*/
void	handle_mlx_bonus_features(t_data *data, int keycode);

#endif // !PPROC_H
