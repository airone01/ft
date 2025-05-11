/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_big_brother.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:10:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 17:08:05 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	launch_big_brother(t_ctx *ctx, pthread_t *big_brother)
{
	if (pthread_create(big_brother, NULL, death_check, ctx) != 0)
	{
		ctx->stop = 1;
		return (true);
	}
	return (false);
}
