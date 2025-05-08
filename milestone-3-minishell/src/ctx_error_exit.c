/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_error_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:07:35 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 14:09:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "free.h"

/**
 * @brief Frees context, displays an error and quits with the corresponding
 * exit code
 *
 * @param ctx Context
 * @param proof (optional) Proof that the error occured
 * @param module (optional) Module where the error occured
 * @param err Error code
 */
void	ctx_error_exit(t_ctx *ctx, const char *proof, const char *module,
		t_error_type err)
{
	if (ctx)
		ctx_clear(ctx);
	exit(error(proof, module, err));
}
