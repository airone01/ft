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

/*
** Handle the case where there is only one philosopher
*/
static void	*take_fork_and_return(t_philo *philo)
{
	log_action(philo, MSG_TAKEN);
	std_usleep(philo->ctx->death_time, philo);
	return (NULL);
}

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
		mx_gbool(&ctx->ctx_mtx, &ctx->all_threads_ready, &started);
		if (!started)
			std_usleep(5, NULL);
	}
}

/*
** Here we return the result of the stop flag in log_action to avoid having
** to (un)lock too many times.
**
** Note: to patch the issue of the 3rd philo being stolen its fork by the 1st,
** we use this weird trick (tbh it's duct tape but it works) which sleeps for
** a very specific amout of time after thinking. wtf. I don't question it.
*/
void	*routine(void *arg)
{
	t_philo	*philo;
	bool	stop;

	philo = (t_philo *)arg;
	wait_all_philos(philo->ctx);
	if (philo->ctx->philos_count == 1)
		return (take_fork_and_return(philo));
	log_action(philo, MSG_THINK);
	if (philo->id % 2 == 0)
		std_usleep(philo->ctx->meal_time / 10, philo);
	mx_gbool(&philo->ctx->ctx_mtx, &philo->ctx->stop, &stop);
	while (!stop)
	{
		eat(philo);
		if (log_action(philo, MSG_SLEEP))
			break ;
		std_usleep(philo->ctx->sleep_time, philo);
		if (log_action(philo, MSG_THINK))
			break ;
		if (philo->ctx->philos_count == 3)
			std_usleep((philo->id * 7) % 17, philo);
	}
	return (NULL);
}
