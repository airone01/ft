/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:38:23 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/26 11:39:39 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	launch_philos(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->philos_count)
	{
		if (pthread_create(&ctx->philos[i].thread, NULL, routine,
				&ctx->philos[i]) != 0)
		{
			ctx->stop = true;
			while (--i >= 0)
				pthread_join(ctx->philos[i].thread, NULL);
			return (true);
		}
	}
	return (false);
}
