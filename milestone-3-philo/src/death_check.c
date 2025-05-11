/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:53:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 18:47:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if a philo died
 */
static int	grim_reaper_check(t_ctx *ctx, int i)
{
	size_t	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&ctx->print_lock);
	if ((long)(current_time - ctx->philos[i].last_meal) > ctx->death_time)
	{
		pthread_mutex_lock(&ctx->dead_lock);
		ctx->stop = 1;
		printf("%zu %lu died\n", current_time - ctx->epoch, ctx->philos[i].id);
		pthread_mutex_unlock(&ctx->dead_lock);
		pthread_mutex_unlock(&ctx->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&ctx->print_lock);
	return (0);
}

/**
 * @brief Checks if all philos are full (meaning they ate)
 */
static bool	chef_gusteau_check(t_ctx *ctx)
{
	long	i;
	bool	all_ate;

	i = -1;
	all_ate = true;
	while (++i < ctx->philos_count)
	{
		pthread_mutex_lock(&ctx->print_lock);
		if (ctx->philos[i].meal_count < ctx->max_meal_count
			|| ctx->max_meal_count == -1)
			all_ate = false;
		pthread_mutex_unlock(&ctx->print_lock);
	}
	return (all_ate);
}

void	*death_check(void *arg)
{
	t_ctx	*ctx;
	int		i;

	ctx = (t_ctx *)arg;
	while (1)
	{
		i = -1;
		while (++i < ctx->philos_count)
			if (grim_reaper_check(ctx, i))
				return (NULL);
		if (chef_gusteau_check(ctx))
		{
			pthread_mutex_lock(&ctx->print_lock);
			pthread_mutex_lock(&ctx->dead_lock);
			ctx->stop = true;
			write(STDERR_FILENO,
				"All philosophers ate the maximum number of meals\n", 49);
			pthread_mutex_unlock(&ctx->dead_lock);
			pthread_mutex_unlock(&ctx->print_lock);
			break ;
		}
		usleep(1);
	}
	return (NULL);
}
