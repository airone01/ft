/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:19:21 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 17:12:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "philo.h"

int	init_mutexes(t_ctx *ctx)
{
	unsigned int	i;
	int				code;

	i = 0;
	ctx->mutexes = ft_calloc(ctx->philos_count, sizeof(pthread_mutex_t *));
	if (!ctx->mutexes)
		return (_rf(ctx, ENOMEM));
	while (i < ctx->philos_count)
	{
		ctx->mutexes[i] = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!ctx->mutexes[i])
			return (_rf(ctx, ENOMEM));
		code = pthread_mutex_init(ctx->mutexes[i], NULL);
		if (code)
			return (_rf(ctx, code));
		i++;
	}
	return (0);
}
