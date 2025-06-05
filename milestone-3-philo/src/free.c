/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:04:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/26 15:44:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Finite resource cleaning
*/

#include "philo.h"
#include <stdlib.h> // free()

void	destroy_fork_mutexes(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->fork_mtx_created)
	{
		pthread_mutex_destroy(&ctx->forks[i].mtx);
		i++;
	}
}

static void	destroy_all_mutexes(t_ctx *ctx)
{
	if (ctx->fork_mtx_created > 0)
		destroy_fork_mutexes(ctx);
	if (ctx->print_mtx_created)
		pthread_mutex_destroy(&ctx->print_mtx);
	if (ctx->ctx_mtx_created)
		pthread_mutex_destroy(&ctx->ctx_mtx);
}

void	free_ctx(t_ctx *ctx)
{
	if (!ctx)
		return ;
	destroy_all_mutexes(ctx);
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
