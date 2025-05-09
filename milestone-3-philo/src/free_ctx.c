/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:04:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 17:13:30 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "philo.h"

int	_rf(t_ctx *ctx, int status)
{
	free_ctx(ctx);
	return (status);
}

void	free_ctx(t_ctx *ctx)
{
	free_mutexes(ctx);
	free(ctx);
}
