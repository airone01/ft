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
#include <unistd.h>
#include <stdio.h>

void	log_action(t_philo *philo, const char *action)
{
	unsigned long	l;

	l = get_current_time();
	if (is_it_over(philo->ctx))
		return ;
	pthread_mutex_lock(&philo->ctx->print_lock);
	printf("%zu %lu %s\n", l - philo->ctx->epoch, philo->id, action);
	pthread_mutex_unlock(&philo->ctx->print_lock);
}

int	mtx_get(pthread_mutex_t *mtx, uint8_t *origin, uint8_t *dest)
{
	int	code;

	code = pthread_mutex_lock(mtx);
	if (code)
	{
		write(STDERR_FILENO, "There was an error locking a mutex.\n", 36);
		return (code);
	}
	*dest = *origin;
	code = pthread_mutex_unlock(mtx);
	if (code)
	{
		write(STDERR_FILENO, "There was an error locking a mutex.\n", 36);
		return (code);
	}
	return (0);
}

int	mtx_set(pthread_mutex_t *mtx, uint8_t *dest, uint8_t val)
{
	int	code;

	code = pthread_mutex_lock(mtx);
	if (code)
	{
		write(STDERR_FILENO, "There was an error locking a mutex.\n", 36);
		return (code);
	}
	*dest = val;
	code = pthread_mutex_unlock(mtx);
	if (code)
	{
		write(STDERR_FILENO, "There was an error locking a mutex.\n", 36);
		return (code);
	}
	return (0);
}
