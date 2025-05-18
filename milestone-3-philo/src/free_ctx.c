/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:04:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/18 15:11:11 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "philo.h"

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
