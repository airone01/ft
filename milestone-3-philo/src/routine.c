/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:40:45 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 18:42:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	log_action(t_philo *philo, const char *msg)
{
	struct timeval	now;
	long			timestamp;

	if (!msg)
		return ;
	pthread_mutex_lock(&philo->ctx->print_lock);
	if (philo->ctx->stop)
	{
		pthread_mutex_unlock(&philo->ctx->print_lock);
		return ;
	}
	gettimeofday(&now, NULL);
	timestamp = (now.tv_sec - philo->ctx->epoch.tv_sec) * 1000 + (now.tv_usec
			- philo->ctx->epoch.tv_usec) / 1000;
	ft_printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->ctx->print_lock);
}

static void	ft_usleep(unsigned long time)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(500);
		gettimeofday(&current, NULL);
		if ((current.tv_sec - start.tv_sec) * 1000 + (current.tv_usec
				- start.tv_usec) / 1000 >= (long)time)
			break ;
	}
}

void	*routine(t_philo *philo)
{
	t_ctx			*ctx;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	ctx = philo->ctx;
	left_fork = ctx->mutexes[(philo->id - 1)];
	right_fork = ctx->mutexes[philo->id % ctx->philos_count];
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&ctx->print_lock);
		pthread_mutex_unlock(&ctx->print_lock);
		if (ctx->stop)
			break ;
		log_action(philo, "is thinking");
		pthread_mutex_lock(left_fork);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(right_fork);
		log_action(philo, "has taken a fork");
		gettimeofday(&philo->last_meal, NULL);
		log_action(philo, "is eating");
		ft_usleep(ctx->meal_time);
		philo->meal_count++;
		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);
		log_action(philo, "is sleeping");
		ft_usleep(ctx->sleep_time);
	}
	return (NULL);
}
