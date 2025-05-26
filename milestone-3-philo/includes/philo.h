/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:10:28 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/26 15:44:05 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h" // GPM!
// GPM!
# include "std.h"      // my standard functions
# include <errno.h>    // for error types such as ENOMEM
# include <limits.h>   // integer limits
# include <pthread.h>  // threading
# include <stdbool.h>  // booleans
# include <stdint.h>   // for SIZE_MAX
# include <stdio.h>    // printf
# include <stdlib.h>   // standard lib
# include <sys/time.h> // for gettimeofday
# include <unistd.h>   // usleep

# define FG_RED "\x1b[31m"
# define FG_GREEN "\x1b[32m"
# define FG_YELLOW "\x1b[33m"
# define NC "\x1b[0m"

// *************************************************************************** #
//                                 Structures                                  #
// *************************************************************************** #

/**
 * @brief Information about a fork
 */
typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			in_use;
}					t_fork;

/**
 * @brief Informations about a philosopher
 */
typedef struct s_philo
{
	long			id;
	long			meal_count;
	unsigned long	last_meal;
	pthread_t		thread;
	struct s_ctx	*ctx;
	t_fork			*fork_right;
	t_fork			*fork_left;
}					t_philo;

/**
 * @brief Contains basic app info (parsed through arguments)
 */
typedef struct s_ctx
{
	// CLI arguments
	long			philos_count;
	long			death_time;
	long			meal_time;
	long			sleep_time;
	long			max_meal_count;
	// Mutexes
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	t_fork			*forks;
	// Start time
	unsigned long	epoch;
	// Philosophers
	t_philo			*philos;
	// Mission control
	bool			stop;
	pthread_mutex_t	start_mutex;
	int				threads_ready;
	bool			simulation_started;
}					t_ctx;

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
 * @brief Calculates the time each philo has to think
 *
 * @param philo Philosopher
 * @return unsigned long Time to think
 */
unsigned long		calculate_thinking_time(t_philo *philo);

/**
 * @brief Checks for the death of philosophers
 *
 * @param arg Argument
 * @return void* Unused
 */
void				*death_check(void *arg);

/**
 * @brief Sleeps for a given number of milliseconds, with early exit if the
 *        simulation ends.
 *
 * This function behaves like a standard sleep but periodically checks whether
 * the simulation is over. If so, it exits early to avoid unnecessary blocking.
 *
 * @param milliseconds Duration to sleep, in milliseconds.
 * @param philo Pointer to the philosopher, used to access the simulation
 *              context.
 */
void				ft_usleep(unsigned long milliseconds, t_philo *philo);

/**
 * @brief Get the current time in epoch unsigned long format
 *
 * @return long Time
 */
unsigned long		get_current_time(void);

/**
 * @brief Checks whether the simulation has been marked as over.
 *
 * Safely reads the shared simulation stop flag using a mutex to ensure
 * thread-safe access.
 *
 * @param ctx Pointer to the simulation context.
 * @return true if the simulation is over, false otherwise.
 */
bool				is_it_over(t_ctx *ctx);

/**
 * @brief Launches philosopher threads to start the simulation.
 *
 * Creates one thread per philosopher, each running the simulation routine.
 * If thread creation fails for any philosopher, the simulation is marked as
 * stopped and the function returns true to indicate failure.
 *
 * @param ctx Pointer to the simulation context.
 * @param created_threads Number of threads that were actually created
 * @return true if an error occurred during thread creation, false on success.
 */
bool				launch_philos(t_ctx *ctx, int *created_threads);

/**
 * @brief Launches the monitoring thread for the simulation.
 *
 * Starts a detached thread that continuously monitors the philosophers'
 * state (e.g., death detection or completion conditions). If the thread
 * fails to launch, the function returns true to signal an error.
 *
 * @param ctx Simulation context (passed by value).
 * @param big_brother Master thread
 * @return true if thread creation failed, false on success.
 */
bool				launch_big_brother(t_ctx *ctx, pthread_t *big_brother);

/**
 * @brief Logs an action performed by a philosopher.
 *
 * This function prints a timestamped message describing the action taken by
 * the given philosopher. It ensures thread-safe printing using a mutex and
 * does not log anything if the simulation is over.
 *
 * @param philo Pointer to the philosopher structure.
 * @param action Description of the action to log (e.g., "is eating",
	"is thinking").
 */
void				log_action(t_philo *philo, const char *action);

/**
 * @brief Routine for each threaad
 *
 * @param arg Argument
 * @return void* Unused
 */
void				*routine(void *arg);

/**
 * @brief Acquires both forks needed by the philosopher to eat.
 *
 * This function locks the forks (usually represented by mutexes) associated
 * with the philosopher. The order of locking may depend on the philosopher's
 * ID to avoid deadlocks.
 *
 * @param philo Pointer to the philosopher attempting to take the forks.
 */
void				take_forks(t_philo *philo);

/**
 * @brief Updates a philosopher's state after taking forks and begins the eating
 *        phase.
 *
 * This function logs that the philosopher is eating, updates the time of the
 * last meal and the meal count (with synchronization), then sleeps for the
 * duration of the eating period. Afterward, it releases the forks in an
 * order based on the philosopher's ID to help prevent deadlocks.
 *
 * @param philo Pointer to the philosopher whose state is being updated.
 */
void				update_philo(t_philo *philo);

#endif
