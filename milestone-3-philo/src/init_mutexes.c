/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:19:21 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/26 15:22:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* I don't care enough for this to have its own header entry */
void	destroy_fork_mutexes(t_ctx *ctx);

static bool	init_fork_mutexes(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->philos_count)
	{
		if (pthread_mutex_init(&ctx->forks[i].mtx, NULL))
		{
			destroy_fork_mutexes(ctx);
			return (true);
		}
		ctx->fork_mtx_created = i;
		ctx->forks[i].in_use = false;
	}
	return (false);
}

bool	init_mutexes(t_ctx *ctx)
{
	if (pthread_mutex_init(&ctx->print_mtx, NULL)
		|| pthread_mutex_init(&ctx->ctx_mtx, NULL)
		|| init_fork_mutexes(ctx))
	{
		free_ctx(ctx);
		return (true);
	}
	return (false);
}
