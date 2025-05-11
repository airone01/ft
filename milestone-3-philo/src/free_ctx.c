/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:04:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 17:39:26 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "philo.h"

int	_rf(t_ctx *ctx, int status)
{
	free_ctx(ctx);
	return (status);
}

void	free_ctx(t_ctx *ctx)
{
	if (ctx->philos)
	{
		free(ctx->philos);
		ctx->philos = NULL;
	}
	if (ctx->forks)
	{
		free(ctx->forks);
		ctx->forks = NULL;
	}
	free(ctx);
}
