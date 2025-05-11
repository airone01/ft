/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:40:45 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 13:49:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	log_action(t_philo *philo, const char *msg)
{
	struct timeval	now;
	long			timestamp;
	bool			should_continue_;

	if (!msg)
		return ;
	pthread_mutex_lock(&philo->ctx->print_lock);
	should_continue_ = !philo->ctx->stop;
	if (should_continue_)
	{
		gettimeofday(&now, NULL);
		timestamp = (now.tv_sec - philo->ctx->epoch.tv_sec) * 1000;
		timestamp += (now.tv_usec - philo->ctx->epoch.tv_usec) / 1000;
		printf("%ld %lu %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->ctx->print_lock);
}

/**
 * @brief Custom sleep function with microsecond precision
 *
 * This function sleeps for the specified amount of microseconds by performing
 * short usleep intervals and checking elapsed time. This approach allows for
 * more accurate timing than a single usleep call.
 *
 * @param time Time to sleep in microseconds
 */
static void	ft_usleep(unsigned long time)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(500);
		gettimeofday(&current, NULL);
		elapsed = (current.tv_sec - start.tv_sec) * 1000000;
		elapsed += (current.tv_usec - start.tv_usec);
		if (elapsed >= (long)time)
			break ;
	}
}

void	*routine(t_philo *philo)
{
	t_ctx			*ctx;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	bool			should_continue_;

	ctx = philo->ctx;
	left_fork = ctx->mutexes[(philo->id - 1)];
	right_fork = ctx->mutexes[philo->id % ctx->philos_count];
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&ctx->print_lock);
		should_continue_ = !ctx->stop;
		pthread_mutex_unlock(&ctx->print_lock);
		if (!should_continue_)
			break ;
		log_action(philo, "is thinking");
		pthread_mutex_lock(left_fork);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(right_fork);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(&ctx->print_lock);
		should_continue_ = !ctx->stop;
		if (should_continue_)
		{
			gettimeofday(&philo->last_meal, NULL);
			pthread_mutex_unlock(&ctx->print_lock);
			log_action(philo, "is eating");
			ft_usleep(ctx->meal_time);
			philo->meal_count++;
		}
		else
			pthread_mutex_unlock(&ctx->print_lock);
		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_lock(&ctx->print_lock);
		should_continue_ = !ctx->stop;
		pthread_mutex_unlock(&ctx->print_lock);
		if (!should_continue_)
			break ;
		log_action(philo, "is sleeping");
		ft_usleep(ctx->sleep_time);
	}
	return (NULL);
}
