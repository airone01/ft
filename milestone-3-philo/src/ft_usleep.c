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
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

long	get_time(t_time_code code)
{
	struct timeval	time;
	long			s;
	long			us;

	gettimeofday(&time, NULL);
	s = time.tv_sec;
	us = time.tv_usec;
	if (code == TIMEE_S)
		return (s + (us / (long)1e6));
	if (code == TIMEE_MS)
		return ((s * (long)1e3) + (us / (long)1e3));
	if (code == TIMEE_US)
		return ((s * (long)1e6) + us);
	return (-1);
}

void	ft_usleep(long wait_time, t_philo *philo)
{
	long	start;

	start = get_time(TIMEE_MS);
	while ((get_time(TIMEE_MS) - start) < wait_time)
	{
		if (philo && mtx_get_bool(&philo->ctx->ctx_mtx, &philo->ctx->stop))
			return ;
		usleep(ARBITRARY_USLEEP_TIME);
	}
}
