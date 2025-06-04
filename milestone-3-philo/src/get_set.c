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
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

bool	log_action(t_philo *philo, const char *action)
{
	long	ms;

	ms = get_time(TIMEE_US);
	if (mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
		return (true);
	pthread_mutex_lock(&philo->ctx->print_mtx);
	printf("%zu %lu %s\n", (ms - philo->ctx->epoch) / 1000, philo->id, action);
	pthread_mutex_unlock(&philo->ctx->print_mtx);
	return (false);
}

bool	mtx_get_bool(pthread_mutex_t *mtx, bool *origin)
{
	bool	dest;

	pthread_mutex_lock(mtx);
	dest = *origin;
	pthread_mutex_unlock(mtx);
	return (dest);
}

void	mtx_set_bool(pthread_mutex_t *mtx, bool *dest, bool val)
{
	pthread_mutex_lock(mtx);
	*dest = val;
	pthread_mutex_unlock(mtx);
}

void	mtx_set_long(pthread_mutex_t *mtx, long *dest, long val)
{
	pthread_mutex_lock(mtx);
	*dest = val;
	pthread_mutex_unlock(mtx);
}

void	mtx_increment_long(pthread_mutex_t *mtx, long *dest)
{
	pthread_mutex_lock(mtx);
	*dest += 1;
	pthread_mutex_unlock(mtx);
}
