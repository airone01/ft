/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:38:23 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 18:11:33 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_philos(t_ctx *ctx, t_philo *philos)
{
	unsigned int	i;

	i = 0;
	while (i < ctx->philos_count)
	{
		pthread_create(&philos[i].thread, NULL, (void *(*)(void *))routine,
			&philos[i]);
		i++;
	}
}
