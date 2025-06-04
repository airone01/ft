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

static void	take_forks(t_philo *philo, t_fork *f1, t_fork *f2)
{
	bool	stop;

	mx_gbool(&philo->ctx->ctx_mtx, &philo->ctx->stop, &stop);
	while (!stop)
	{
		if (try_take_fork(f1))
		{
			log_action(philo, MSG_TAKEN);
			break;
		}
		usleep(ARBITRARY_USLEEP_TIME);
	}
	mx_gbool(&philo->ctx->ctx_mtx, &philo->ctx->stop, &stop);
	while (!stop)
	{
		if (try_take_fork(f2))
		{
			log_action(philo, MSG_TAKEN);
			break;
		}
		usleep(ARBITRARY_USLEEP_TIME);
	}
}

/*
** Note 1: We do not care about the result of log_action at the end
** of this function, because all the steps done after it need to be done
** regardless of the stop flag.
**
** Note 2: the mx_sbool calls are us releasing the forks (◕‿◕✿)
*/
void	eat(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;
	bool	stop;

	mx_gbool(&philo->ctx->ctx_mtx, &philo->ctx->stop, &stop);
	if (stop)
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
	mx_gbool(&philo->ctx->ctx_mtx, &philo->ctx->stop, &stop);
	if (stop)
	{
		mx_sbool(&first->mutex, &first->in_use, false);
		mx_sbool(&second->mutex, &second->in_use, false);
		return;
	}
	pthread_mutex_lock(&philo->meal_mtx);
	philo->last_meal = get_time(TIMEE_US);
	pthread_mutex_unlock(&philo->meal_mtx);
	log_action(philo, MSG_EATIN);
	ft_usleep(philo->ctx->meal_time, philo);
	mx_ilong(&philo->meal_mtx, &philo->meal_count);
	mx_sbool(&first->mutex, &first->in_use, false);
	mx_sbool(&second->mutex, &second->in_use, false);
}
