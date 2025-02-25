/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_toggle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:52:39 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 10:52:43 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Toggle a specific debug mode flag
 *
 * @param ctx Application context
 * @param flag The debug flag to toggle
 */
void	toggle_debug_mode(t_app *ctx, int flag)
{
	if (ctx->debug_mode & flag)
		ctx->debug_mode &= ~flag;
	else
		ctx->debug_mode |= flag;
	ctx->needs_render = true;
}
