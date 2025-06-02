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
			ft_usleep(50, NULL);
	}
}

/*
** TODO
** We can consider returning the value of the stop var oin log_action and
** ft_usleep to avoid (un)locking the mutex two times here.
*/
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_philos(philo->ctx);
	if (philo->ctx->philos_count == 1)
		return (take_fork_and_return(philo));
	log_action(philo, MSG_THINK);
	while (!mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
	{
		// if (philo->id % 2 == 0)
		// 	usleep(ARBITRARY_USLEEP_TIME);
		eat(philo);
		if (mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
			break ;
		log_action(philo, MSG_SLEEP);
		ft_usleep(philo->ctx->sleep_time, philo);
		log_action(philo, MSG_THINK);
	}
	return (NULL);
}
