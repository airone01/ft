/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:10:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 17:08:05 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	launch_monitor(t_ctx *ctx, pthread_t *big_brother)
{
	if (pthread_create(big_brother, NULL, routine_monitor, ctx) != 0)
	{
		ctx->stop = true;
		return (true);
	}
	ctx->monitor_launched = true;
	return (false);
}
