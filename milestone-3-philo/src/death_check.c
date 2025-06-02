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
#include <stdint.h>

/*
** Checks if a philo died
** /!\ There may be a data race here
*/
static int	grim_reaper_check(t_ctx *ctx, int i)
{
	size_t	current_time;

	current_time = get_current_time();
	if ((long)(current_time - ctx->philos[i].last_meal) > ctx->death_time
		/ 1000)
	{
		mtx_set(&ctx->dead_lock, (uint8_t *)&ctx->stop, 1); /* TODO: handle return val here */
		log_action(&ctx->philos[i], "died");
		return (1);
	}
	return (0);
}

/*
** Checks if all philos are full (meaning they all ate)
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

/*
** When all philos are full, this writes some info to stderr.
*/
static void	write_thats_all_folks(t_ctx *ctx)
{
	char	*s;

	s = ft_itoa((int)ctx->max_meal_count);
	if (!s)
		return ;
	write(STDERR_FILENO,
		FG_GREEN "All philosophers ate the maximum number of meals (", 55);
	write(STDERR_FILENO, s, ft_strlen(s));
	free(s);
	write(STDERR_FILENO, ").\n" NC, 7);
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
			write_thats_all_folks(ctx);
			pthread_mutex_unlock(&ctx->dead_lock);
			pthread_mutex_unlock(&ctx->print_lock);
			break ;
		}
		usleep(1);
	}
	return (NULL);
}
