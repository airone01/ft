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

/*
** Better and more precise impementation
**
** - usleep most of the time to not consume CPU
** - we loop over for last microsecs
*/
void	ft_usleep(long wait_time, t_philo *philo)
{
	long	start;
	bool	stop;

	start = get_time(TIMEE_MS);
	while ((get_time(TIMEE_MS) - start) < wait_time)
	{
		if (philo)
		{
			mx_gbool(&philo->ctx->ctx_mtx, &philo->ctx->stop, &stop);
			if (stop)
				break ;
		}
		if ((double)(wait_time - get_time(TIMEE_US)) > 1e3)
			usleep((unsigned int)wait_time);
		else
			while (get_time(TIMEE_US) - start < wait_time)
				;
		usleep(ARBITRARY_USLEEP_TIME);
	}
}
