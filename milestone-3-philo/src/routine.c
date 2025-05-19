/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:40:45 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/19 13:22:00 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Handle the case where there is only one philosopher
*/
static void	*take_fork_and_return(t_philo *philo)
{
	log_action(philo, "has taken a fork");
	ft_usleep((unsigned long)philo->ctx->death_time, philo);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->ctx->start_mutex);
	philo->ctx->threads_ready++;
	if (philo->ctx->threads_ready == philo->ctx->philos_count)
		philo->ctx->simulation_started = true;
	pthread_mutex_unlock(&philo->ctx->start_mutex);
	while (!philo->ctx->simulation_started)
		usleep(100);
	if (philo->ctx->philos_count == 1)
		return (take_fork_and_return(philo));
	if (philo->id == 1)
		log_action(philo, "is thinking");
	if (philo->id % 2 == 0)
	{
		log_action(philo, "is thinking");
		ft_usleep(calculate_thinking_time(philo), philo);
	}
	while (!is_it_over(philo->ctx))
	{
		take_forks(philo);
		update_philo(philo);
		if (is_it_over(philo->ctx))
			break ;
		log_action(philo, "is sleeping");
		ft_usleep((unsigned long)philo->ctx->sleep_time, philo);
		if (is_it_over(philo->ctx))
			break ;
		log_action(philo, "is thinking");
		ft_usleep(calculate_thinking_time(philo), philo);
	}
	return (NULL);
}
