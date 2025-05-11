/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:51:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 17:51:26 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_philo *philo, const char *action)
{
	unsigned long	l;

	l = get_current_time();
	if (is_it_over(philo->ctx))
		return ;
	pthread_mutex_lock(&philo->ctx->print_lock);
	if (!is_it_over(philo->ctx))
		printf("%zu %lu %s\n", l - philo->ctx->epoch, philo->id, action);
	pthread_mutex_unlock(&philo->ctx->print_lock);
}
