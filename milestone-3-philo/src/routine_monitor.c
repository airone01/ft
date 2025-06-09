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

/*
** This file is where all the logic of the philos dying lies.
*/

#include "philo.h"
#include "std.h"
#include <stdio.h>  // printf()
#include <stdlib.h> // free()
#include <unistd.h> // write(), usleep(), STDERR_FILENO

/*
** This checks if
*/
static bool	are_philos_alive(t_ctx *ctx, int i)
{
	long	current_time;

	current_time = get_time(TIMEE_US);
	if ((current_time - ctx->philos[i].last_meal) / 1000 > ctx->death_time)
	{
		mx_sbool(&ctx->ctx_mtx, &ctx->stop, true);
		pthread_mutex_lock(&ctx->philos[i].ctx->print_mtx);
		printf("%zu %lu %s\n", (current_time - ctx->epoch) / 1000,
			ctx->philos[i].id, MSG_DEATH);
		pthread_mutex_unlock(&ctx->philos[i].ctx->print_mtx);
		return (true);
	}
	return (false);
}

static bool	are_philos_full(t_ctx *ctx)
{
	bool	all_full;
	long	i;

	i = -1;
	all_full = true;
	while (++i < ctx->philos_count)
	{
		pthread_mutex_lock(&ctx->philos[i].meal_mtx);
		if (ctx->philos[i].meal_count < ctx->max_meal_count
			|| ctx->max_meal_count == -1)
			all_full = false;
		pthread_mutex_unlock(&ctx->philos[i].meal_mtx);
	}
	return (all_full);
}

/*
** When all philos are full, this writes some info to stderr to make sure
** it is displayed even if you redirect STDOUT.
*/
static void	write_green_message(t_ctx *ctx)
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

void	*routine_monitor(void *arg)
{
	t_ctx	*ctx;
	bool	stop;
	int		i;

	ctx = (t_ctx *)arg;
	wait_all_philos(ctx);
	while (true)
	{
		mx_gbool(&ctx->ctx_mtx, &ctx->stop, &stop);
		if (stop)
			break ;
		i = -1;
		while (++i < ctx->philos_count)
			if (are_philos_alive(ctx, i))
				return (NULL);
		if (are_philos_full(ctx))
		{
			mx_sbool(&ctx->ctx_mtx, &ctx->stop, true);
			write_green_message(ctx);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
