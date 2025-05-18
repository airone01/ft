/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:19:21 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/18 13:06:55 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "philo.h"

int	init_mutexes(t_ctx *ctx)
{
	int	i;

	if (pthread_mutex_init(&ctx->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&ctx->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&ctx->print_lock);
		return (1);
	}
	i = -1;
	while (++i < ctx->philos_count)
	{
		if (pthread_mutex_init(&ctx->forks[i].mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&ctx->forks[i].mutex);
			pthread_mutex_destroy(&ctx->print_lock);
			pthread_mutex_destroy(&ctx->dead_lock);
			return (1);
		}
		ctx->forks[i].in_use = false;
		ctx->forks[i].owner_id = -1;
	}
	return (0);
}
