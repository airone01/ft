/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:39:19 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 18:28:23 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutexes(t_ctx *ctx)
{
	unsigned int	i;
	int				code;

	if (!ctx->mutexes)
		return ;
	i = 0;
	while (i < ctx->philos_count)
	{
		if (ctx->mutexes[i])
		{
			code = pthread_mutex_destroy(ctx->mutexes[i]);
			if (code)
				ft_printf_fd(STDERR_FILENO,
					"Failed to destroy mutex #%d. Code is %d\n", i, code);
			free(ctx->mutexes[i]);
			ctx->mutexes[i] = NULL;
		}
		i++;
	}
	pthread_mutex_destroy(&ctx->print_lock);
	free(ctx->mutexes);
	ctx->mutexes = NULL;
}
