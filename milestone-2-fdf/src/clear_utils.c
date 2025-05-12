/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:37:14 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:19:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Clears the context and exits normally
 *
 * @param ctx Context
 */
void	ctx_clear_0(t_ctx *ctx)
{
	ctx_clear(ctx);
	exit(EXIT_SUCCESS);
}
