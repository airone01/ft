/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:10:28 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 16:58:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "ft_printf.h"
# include "libft.h"
# include <errno.h>
# include <limits.h>
# include <pthread.h>

// *************************************************************************** #
//                                 Structures                                  #
// *************************************************************************** #

/**
 * @brief Contains basic app info (parsed through arguments)
 */
typedef struct s_ctx
{
	unsigned long	philos_count;
	unsigned long	death_time;
	unsigned long	meal_time;
	unsigned long	sleep_time;
	unsigned long	meals_count;
	pthread_mutex_t	**mutexes;
}					t_ctx;

/**
 * @brief Represent informations about a philosopher
 */
typedef struct s_philo
{
	int				id;
	t_bool			fork_left;
	t_bool			fork_right;
	int				last_meal_time;
	int				meal_count;
}					t_philo;

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

/**
 * @brief Main entry to the program
 *
 * @param argc Arguments count
 * @param argv Arguments
 * @return int Return status
 */
int					main(int argc, char **argv);

#endif
