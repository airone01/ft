/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:10:28 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 18:30:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "ft_printf.h" // my printf
# include "libft.h"     // my standard lib
# include <errno.h>     // for error types such as ENOMEM
# include <limits.h>    // integer limits
# include <pthread.h>   // threading
# include <sys/time.h>  // for gettimeofday
// # include <sys/wait.h>  // for waitpid

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
	struct timeval	epoch;
	pthread_mutex_t	print_lock;
	t_bool			stop;
}					t_ctx;

/**
 * @brief Represent informations about a philosopher
 */
typedef struct s_philo
{
	unsigned long	id;
	t_bool			fork_left;
	t_bool			fork_right;
	struct timeval	last_meal;
	unsigned long	meal_count;
	pthread_t		thread;
	t_ctx			*ctx;
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

/**
 * @brief Checks for the death of philos
 *
 * @param philos Philosophers
 * @return void* Unused
 */
void				*death_check(t_philo *philos);

/**
 * @brief Launches the threads
 *
 * @param ctx Context
 * @param philos Philosophers
 */
void				launch_philos(t_ctx *ctx, t_philo *philos);

/**
 * @brief Routine for each threaad
 *
 * @param philo Philosopher
 * @return void* Unused
 */
void				*routine(t_philo *philo);

#endif
