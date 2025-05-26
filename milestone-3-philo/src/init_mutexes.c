/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:19:21 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/26 11:38:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "philo.h"

static void	destroy_fork_mutexes(t_ctx *ctx, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		pthread_mutex_destroy(&ctx->forks[i].mutex);
}

static bool	start_all_philos(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->philos_count)
	{
		if (pthread_mutex_init(&ctx->forks[i].mutex, NULL) != 0)
		{
			destroy_fork_mutexes(ctx, i);
			pthread_mutex_destroy(&ctx->print_lock);
			pthread_mutex_destroy(&ctx->dead_lock);
			pthread_mutex_destroy(&ctx->start_mutex);
			free_ctx(ctx);
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
		pthread_mutex_destroy(&ctx->print_lock);
		free_ctx(ctx);
		return (true);
	}
	if (pthread_mutex_init(&ctx->start_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&ctx->print_lock);
		pthread_mutex_destroy(&ctx->dead_lock);
		free_ctx(ctx);
		return (true);
	}
	if (start_all_philos(ctx))
		return (true);
	return (false);
}
