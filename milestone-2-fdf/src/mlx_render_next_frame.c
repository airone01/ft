/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_next_frame.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/20 14:26:17 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/**
 * @brief	Renders the next frame
 *
 * @param	app	Application context
 */
int	render_next_frame(t_app *app)
{
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	return (0);
}
