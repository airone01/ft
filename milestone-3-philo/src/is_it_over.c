/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_over.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:58:19 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 16:58:32 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_it_over(t_ctx *ctx)
{
	bool	result;

	pthread_mutex_lock(&ctx->dead_lock);
	result = ctx->stop;
	pthread_mutex_unlock(&ctx->dead_lock);
	return (result);
}
