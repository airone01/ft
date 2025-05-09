/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:30:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 16:57:54 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_ctx *ctx)
{
	t_philo	*philos;

	philos = ft_calloc(ctx->philos_count, sizeof(t_philo));
	return (philos);
}
