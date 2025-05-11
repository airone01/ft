/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:37:54 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 18:01:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
		log_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		log_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
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
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
}
