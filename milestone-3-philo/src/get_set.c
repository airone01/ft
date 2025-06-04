/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:04:42 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/02 12:04:42 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> // printf()

/*
** As of 5c8fd67, this no longer glitches with the death
** message because we lock print_mtx and ctx_mtx at the same time.
** A side effect of that was slowing down the program when there are a large
** amount of philosophers.
** It should now be fast enough on Lyon's DELL PCs.
*/
bool	log_action(t_philo *philo, const char *action)
{
	bool	stop;
	long	ms;

	ms = get_time(TIMEE_US);
	pthread_mutex_lock(&philo->ctx->print_mtx);
	mx_gbool(&philo->ctx->ctx_mtx, &philo->ctx->stop, &stop);
	if (stop)
	{
		pthread_mutex_unlock(&philo->ctx->print_mtx);
		return (true);
	}
	printf("%zu %lu %s\n", (ms - philo->ctx->epoch) / 1000, philo->id, action);
	pthread_mutex_unlock(&philo->ctx->print_mtx);
	return (false);
}

void	mx_gbool(pthread_mutex_t *mtx, bool *origin, bool *dest)
{
	pthread_mutex_lock(mtx);
	*dest = *origin;
	pthread_mutex_unlock(mtx);
}

void	mx_sbool(pthread_mutex_t *mtx, bool *dest, bool val)
{
	pthread_mutex_lock(mtx);
	*dest = val;
	pthread_mutex_unlock(mtx);
}

void	mx_slong(pthread_mutex_t *mtx, long *dest, long val)
{
	pthread_mutex_lock(mtx);
	*dest = val;
	pthread_mutex_unlock(mtx);
}

void	mx_ilong(pthread_mutex_t *mtx, long *dest)
{
	pthread_mutex_lock(mtx);
	*dest += 1;
	pthread_mutex_unlock(mtx);
}
