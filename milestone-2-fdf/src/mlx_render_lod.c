/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_lod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:10:27 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 09:24:08 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Finds the appropriate LOD depending on the scale
 *
 * @return The appropriate LOD level
 */
int	get_appropriate_lod(t_app *ctx)
{
	if (ctx->scale < 0.5)
		return (LOD_VERY_LOW);
	else if (ctx->scale < 1.0)
		return (LOD_LOW);
	else if (ctx->scale < 2.0)
		return (LOD_MEDIUM);
	else
		return (LOD_HIGH);
}
