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

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_right->mutex);
		philo->fork_right->in_use = true;
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork_left->mutex);
		philo->fork_left->in_use = true;
		log_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->fork_left->mutex);
		philo->fork_left->in_use = true;
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork_right->mutex);
		philo->fork_right->in_use = true;
		log_action(philo, "has taken a fork");
	}
}

void	update_philo(t_philo *philo)
{
	log_action(philo, "is eating");
	pthread_mutex_lock(&philo->ctx->print_lock);
	philo->last_meal = get_current_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->ctx->print_lock);
	ft_usleep((unsigned long)philo->ctx->meal_time, philo);
	if (philo->id % 2 == 0)
	{
		philo->fork_right->in_use = false;
		pthread_mutex_unlock(&philo->fork_right->mutex);
		philo->fork_left->in_use = false;
		pthread_mutex_unlock(&philo->fork_left->mutex);
	}
	else
	{
		philo->fork_left->in_use = false;
		pthread_mutex_unlock(&philo->fork_left->mutex);
		philo->fork_right->in_use = false;
		pthread_mutex_unlock(&philo->fork_right->mutex);
	}
}

unsigned long	calculate_thinking_time(t_philo *philo)
{
	unsigned long	thinking_time;

	thinking_time = 0;
	thinking_time = ((unsigned long)philo->ctx->death_time / 1000
			- (unsigned long)philo->ctx->meal_time / 1000
			- (unsigned long)philo->ctx->sleep_time / 1000) / 2;
	if (philo->id % 2 == 0)
		thinking_time = (unsigned long)((double)thinking_time * 0.9);
	else
		thinking_time = (unsigned long)((double)thinking_time * 1.1);
	if (thinking_time < 1)
		thinking_time = 1;
	return (thinking_time * 1000);
}
