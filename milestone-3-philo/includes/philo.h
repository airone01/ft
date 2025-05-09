/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:10:28 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 17:58:23 by elagouch         ###   ########.fr       */
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
# include <sys/wait.h>  // for waitpid

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
	pthread_t		thread;
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
 * @param fn idk
 * @return void* idk
 */
void				*death_check(void *fn);

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
 * @param fn idk
 * @return void* idk
 */
void				*routine(void *fn);

#endif
