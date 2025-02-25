/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:37:14 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 09:12:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Clears the context and exits normally
 *
 * @param ctx Application context
 */
void	app_clear_0(t_app *ctx)
{
	app_clear(ctx);
	exit(EXIT_SUCCESS);
}
