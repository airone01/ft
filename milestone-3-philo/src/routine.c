/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:40:45 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/26 16:24:08 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

/*
** Handle the case where there is only one philosopher
*/
static void	*take_fork_and_return(t_philo *philo)
{
	log_action(philo, MSG_TAKEN);
	ft_usleep(philo->ctx->death_time, philo);
	return (NULL);
}

/*
** Waits for all philosophers
** Not using mtx_set here as it's way too many operations
**
** TODO: Use all_threads_ready
*/
void	wait_all_philos(t_ctx *ctx)
{
	bool	started;

	pthread_mutex_lock(&ctx->ctx_mtx);
	ctx->threads_ready++;
	if (ctx->threads_ready == ctx->philos_count)
		ctx->all_threads_ready = true;
	started = ctx->all_threads_ready;
	pthread_mutex_unlock(&ctx->ctx_mtx);
	while (!started)
	{
		started = mtx_get_bool(&ctx->ctx_mtx, &ctx->all_threads_ready);
		if (!started)
			ft_usleep(5, NULL);
	}
}

/*
** Here we return the result of the stop flag in log_action to avoid having
** to (un)lock too many times.
*/
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_philos(philo->ctx);
	if (philo->ctx->philos_count == 1)
		return (take_fork_and_return(philo));
	log_action(philo, MSG_THINK);
	if (philo->id % 2 == 0)
		ft_usleep(philo->ctx->meal_time / 10, philo);
	while (!mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
	{
		eat(philo);
		if (log_action(philo, MSG_SLEEP))
			break ;
		ft_usleep(philo->ctx->sleep_time, philo);
		if (log_action(philo, MSG_THINK))
			break ;
	}
	return (NULL);
}
