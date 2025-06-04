/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:53:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/18 15:16:35 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "std.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static bool	grim_reaper_check(t_ctx *ctx, int i)
{
	long	current_time;

	current_time = get_time(TIMEE_US);
	if ((current_time - ctx->philos[i].last_meal) / 1000 > ctx->death_time)
	{
		mtx_set_bool(&ctx->ctx_mtx, &ctx->stop, true);
		pthread_mutex_lock(&ctx->philos[i].ctx->print_mtx);
		printf("%zu %lu %s\n", (current_time - ctx->epoch) / 1000, ctx->philos[i].id,
			MSG_DEATH);
		pthread_mutex_unlock(&ctx->philos[i].ctx->print_mtx);
		return (true);
	}
	return (false);
}

static bool	chef_gusteau_check(t_ctx *ctx)
{
	long	i;
	bool	all_ate;

	i = -1;
	all_ate = true;
	while (++i < ctx->philos_count)
	{
		pthread_mutex_lock(&ctx->philos[i].meal_mtx);
		if (ctx->philos[i].meal_count < ctx->max_meal_count
			|| ctx->max_meal_count == -1)
			all_ate = false;
		pthread_mutex_unlock(&ctx->philos[i].meal_mtx);
	}
	return (all_ate);
}

/*
** When all philos are full, this writes some info to stderr.
*/
static void	write_thats_all_folks(t_ctx *ctx)
{
	char	*s;

	s = ft_itoa((int)ctx->max_meal_count);
	if (!s)
		return ;
	pthread_mutex_lock(&ctx->print_mtx);
	write(STDERR_FILENO,
		FG_GREEN "All philosophers ate the maximum number of meals (", 55);
	write(STDERR_FILENO, s, ft_strlen(s));
	free(s);
	write(STDERR_FILENO, ").\n" NC, 7);
	pthread_mutex_unlock(&ctx->print_mtx);
}

void	*death_check(void *arg)
{
	t_ctx	*ctx;
	int		i;

	ctx = (t_ctx *)arg;
	wait_all_philos(ctx);
	while (true)
	{
		if (mtx_get_bool(&ctx->ctx_mtx, &ctx->stop))
			break ;
		i = -1;
		while (++i < ctx->philos_count)
			if (grim_reaper_check(ctx, i))
				return (NULL);
		if (chef_gusteau_check(ctx))
		{
			mtx_set_bool(&ctx->ctx_mtx, &ctx->stop, true);
			write_thats_all_folks(ctx);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
