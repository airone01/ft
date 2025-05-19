/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:19:21 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/19 12:06:26 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "philo.h"

static bool	start_all_philos(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->philos_count)
	{
		if (pthread_mutex_init(&ctx->forks[i].mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&ctx->forks[i].mutex);
			pthread_mutex_destroy(&ctx->print_lock);
			pthread_mutex_destroy(&ctx->dead_lock);
			return (true);
		}
		ctx->forks[i].in_use = false;
	}
	return (false);
}

bool	init_mutexes(t_ctx *ctx)
{
	if (pthread_mutex_init(&ctx->print_lock, NULL) != 0)
		return (true);
	if (pthread_mutex_init(&ctx->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&ctx->print_lock);
		return (true);
	}
	if (pthread_mutex_init(&ctx->start_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&ctx->print_lock);
		pthread_mutex_destroy(&ctx->dead_lock);
		return (true);
	}
	if (start_all_philos(ctx))
		return (true);
	return (false);
}
