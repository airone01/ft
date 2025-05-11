/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:57:28 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 17:54:32 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (0);
	}
	return ((unsigned long)((time.tv_usec / 1000) + (time.tv_sec * 1000)));
}

void	ft_usleep(unsigned long microseconds, t_philo *philo)
{
	unsigned long	start;
	unsigned long	wait_time;

	start = get_current_time();
	wait_time = microseconds / 1000;
	while ((get_current_time() - start) < wait_time)
	{
		if (is_it_over(philo->ctx))
			return ;
		usleep(1);
	}
}
