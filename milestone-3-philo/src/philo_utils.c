/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:37:54 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/18 15:07:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

static bool	try_take_fork(t_fork *fork)
{
	bool	success;

	pthread_mutex_lock(&fork->mutex);
	success = !fork->in_use;
	if (success)
		fork->in_use = true;
	pthread_mutex_unlock(&fork->mutex);
	return (success);
}

static void release_fork(t_fork *fork)
{
    pthread_mutex_lock(&fork->mutex);
    fork->in_use = false;
    pthread_mutex_unlock(&fork->mutex);
}

static void	take_forks(t_philo *philo, t_fork *f1, t_fork *f2)
{
	while (!mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
	{
		if (try_take_fork(f1))
		{
			log_action(philo, MSG_TAKEN);
			break;
		}
		usleep(ARBITRARY_USLEEP_TIME);
	}
	while (!mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
	{
		if (try_take_fork(f2))
		{
			log_action(philo, MSG_TAKEN);
			break;
		}
		usleep(ARBITRARY_USLEEP_TIME);
	}
}

void	eat(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

	if (mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
		return;
	if (philo->id % 2 == 0)
	{
		first = philo->fork_left;
		second = philo->fork_right;
	}
	else
	{
		first = philo->fork_right;
		second = philo->fork_left;
	}
	take_forks(philo, first, second);
	if (mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
	{
		release_fork(first);
		release_fork(second);
		return;
	}
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal = get_time(TIMEE_US);
	pthread_mutex_unlock(&philo->meal_mtx);
	log_action(philo, MSG_EATIN);
	ft_usleep(philo->ctx->meal_time, philo);
	pthread_mutex_lock(&philo->meal_mtx);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mtx);
	release_fork(first);
	release_fork(second);
}
