/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:53:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 13:09:39 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	time_diff_ms(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) * 1000 + (end->tv_usec
			- start->tv_usec) / 1000);
}

void	*death_check(t_philo *philos)
{
	unsigned int	i;
	struct timeval	now;
	long			timestamp;
	t_ctx			*ctx;
	int				full_count;

	ctx = philos[0].ctx;
	while (1)
	{
		i = 0;
		full_count = 0;
		while (i < ctx->philos_count)
		{
			gettimeofday(&now, NULL);
			if (time_diff_ms(&philos[i].last_meal,
					&now) > (long)ctx->death_time)
			{
				pthread_mutex_lock(&ctx->print_lock);
				timestamp = time_diff_ms(&ctx->epoch, &now);
				if (!ctx->stop)
					printf("%ld %lu died\n", timestamp, philos[i].id);
				ctx->stop = true;
				pthread_mutex_unlock(&ctx->print_lock);
				return (NULL);
			}
			if (ctx->meals_count > 0
				&& philos[i].meal_count >= ctx->meals_count)
				full_count++;
			i++;
		}
		if (ctx->meals_count > 0 && full_count == (int)ctx->philos_count)
		{
			pthread_mutex_lock(&ctx->print_lock);
			ctx->stop = true;
			pthread_mutex_unlock(&ctx->print_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
