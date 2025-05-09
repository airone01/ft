/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:30:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 18:29:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_ctx *ctx)
{
	t_philo			*philos;
	unsigned int	i;

	philos = ft_calloc(ctx->philos_count, sizeof(t_philo));
	i = 0;
	while (i < ctx->philos_count)
	{
		philos[i].id = i + 1;
		philos[i].ctx = ctx;
		philos[i].meal_count = 0;
		philos[i].last_meal = ctx->epoch;
		i++;
	}
	return (philos);
}
