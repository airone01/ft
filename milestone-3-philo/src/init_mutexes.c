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

static void	destroy_fork_mutexes(t_ctx *ctx, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&ctx->forks[i].mutex);
		i++;
	}
}

/*
** To avoid having a lot of boolean args, we use a flag system here
*/
static void	destroy_all_mutexes(t_ctx *ctx, int fork_count, int flags)
{
	if (fork_count > 0)
		destroy_fork_mutexes(ctx, fork_count);
	if (flags & 1)
		pthread_mutex_destroy(&ctx->print_lock);
	if (flags & 2)
		pthread_mutex_destroy(&ctx->dead_lock);
}

static bool	init_fork_mutexes(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->philos_count)
	{
		if (pthread_mutex_init(&ctx->forks[i].mutex, NULL) != 0)
		{
			destroy_fork_mutexes(ctx, i);
			return (true);
		}
		ctx->forks[i].in_use = false;
	}
	return (false);
}

bool	init_mutexes(t_ctx *ctx)
{
	if (pthread_mutex_init(&ctx->print_lock, NULL) != 0)
	{
		free_ctx(ctx);
		return (true);
	}
	if (pthread_mutex_init(&ctx->dead_lock, NULL) != 0)
	{
		destroy_all_mutexes(ctx, 0, 1);
		free_ctx(ctx);
		return (true);
	}
	if (init_fork_mutexes(ctx))
	{
		destroy_all_mutexes(ctx, 0, 3);
		free_ctx(ctx);
		return (true);
	}
	return (false);
}
