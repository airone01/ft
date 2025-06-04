/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:04:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/26 15:44:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h> // free()

void	free_ctx(t_ctx *ctx)
{
	if (!ctx)
		return ;
	if (ctx->philos)
	{
		free(ctx->philos);
		ctx->philos = NULL;
	}
	if (ctx->forks)
	{
		free(ctx->forks);
		ctx->forks = NULL;
	}
	free(ctx);
}
