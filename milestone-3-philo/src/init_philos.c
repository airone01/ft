/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:30:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/18 13:10:23 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

/*
** `last_meal` is set during launch_philos, not here
*/
bool	init_philos(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->philos_count)
	{
		ctx->philos[i].id = i + 1;
		ctx->philos[i].last_meal = ctx->epoch;
		ctx->philos[i].fork_right = &ctx->forks[i];
		ctx->philos[i].fork_left = &ctx->forks[(i + 1) % ctx->philos_count];
		ctx->philos[i].ctx = ctx;
		ctx->philos_created++;
		if (pthread_mutex_init(&ctx->philos[i].meal_mtx, NULL))
		{
			write(STDERR_FILENO, FG_RED ERR_COLON ERR_MUTXC NC,
				ERR_LEN_BASE + ERR_LEN_MUTXC);
			free_ctx(ctx);
			return (true);
		}
		i++;
	}
	i++;
	return (false);
}
