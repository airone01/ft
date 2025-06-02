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

/*
** We don't really have to care about the phread functions return code here.
*/
static bool	set_fork(t_fork *fork)
{
	bool	success;
	int		code;

	success = false;
	code = pthread_mutex_lock(&fork->mutex);
	if (code)
		return (false);
	if (!fork->in_use)
	{
		success = true;
		fork->in_use = true;
	}
	code = pthread_mutex_unlock(&fork->mutex);
	if (code)
		return (false);
	return (success);
}

static void release_fork(t_fork *fork)
{
    pthread_mutex_lock(&fork->mutex);
    fork->in_use = false;
    pthread_mutex_unlock(&fork->mutex);
}

static void	take_fork(t_philo *philo, t_fork *f1, t_fork *f2)
{
	if (mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
		return ;
	while (!set_fork(f1))
		usleep(ARBITRARY_USLEEP_TIME);
	log_action(philo, MSG_TAKEN);
	if (mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
		return ;
	while (!set_fork(f2))
		usleep(ARBITRARY_USLEEP_TIME);
	log_action(philo, MSG_TAKEN);
	if (mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
		return ;
	mtx_set_long(&philo->meal_mtx, &philo->last_meal, get_time(TIMEE_US));
	if (mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
		return ;
	log_action(philo, MSG_EATIN);
	mtx_increment_long(&philo->meal_mtx, &philo->meal_count);
	if (mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
		return ;
	ft_usleep(philo->ctx->meal_time, philo);
	release_fork(f1);
	release_fork(f2);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		take_fork(philo, philo->fork_right, philo->fork_left);
	else
		take_fork(philo, philo->fork_left, philo->fork_right);
}
