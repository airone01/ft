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

# include <pthread.h>  // pthread_*
# include <stdbool.h>  // bool
# include <stdint.h>   // uint8_t

# define FG_RED "\x1b[31m"
# define FG_GREEN "\x1b[32m"
# define FG_YELLOW "\x1b[33m"
# define NC "\x1b[0m"

# define MSG_TAKEN "has taken a fork"
# define MSG_THINK "is thinking"
# define MSG_SLEEP "is sleeping"
# define MSG_EATIN "is eating"
# define MSG_DEATH "died"

# define ERR_USAG1 "Usage: <philos count> <death time> <meal time> <sleep time>"
# define ERR_USAG2 " [meals count]\n"
# define ERR_COLON "Error: "
# define ERR_RANGE "' is out of range for a long integer\n"
# define ERR_NONUM "' contains non-numeric characters\n"
# define ERR_GTIME "gettimeofday() error\n"
# define ERR_PHILC "Philos and meals arguments must be greater than 0.\n"
# define ERR_MALLC "malloc() failed. Is your RAM full?\n"
# define ERR_NOARG "argument is empty\n"
# define ERR_MUTXC "pthread_mutex_init() failed\n"
# define ERR_LUNCH "failed to launch thread(s)\n"

// FG_RED + ERR_COLON + NC = 16

# define ERR_LEN_BASE 16

# define ERR_LEN_USAGE 74
# define ERR_LEN_GTIME 21
# define ERR_LEN_NONUM 34
# define ERR_LEN_MALLC 35
# define ERR_LEN_PHILC 51
# define ERR_LEN_NOARG 18
# define ERR_LEN_MUTXC 28
# define ERR_LEN_LUNCH 27

# define ARBITRARY_USLEEP_TIME 100

// *************************************************************************** #
//                                   Enums                                     #
// *************************************************************************** #

typedef enum e_time_code
{
	TIMEE_S,
	TIMEE_MS,
	TIMEE_US,
}					t_time_code;

// *************************************************************************** #
//                                 Structures                                  #
// *************************************************************************** #

typedef pthread_mutex_t	t_mtx; // Alias
typedef struct s_ctx	t_ctx; // Avoids compilation errors

/**
 * @brief Information about a fork
 */
typedef struct s_fork
{
	t_mtx			mtx;
	bool			in_use;
}					t_fork;

/**
 * @brief Informations about a philosopher
 */
typedef struct s_philo
{
	long			id;
	t_mtx			meal_mtx;
	long			meal_count;
	long			last_meal;
	pthread_t		thread;
	t_ctx			*ctx;
	t_fork			*fork_right;
	t_fork			*fork_left;
}					t_philo;

/**
 * @brief Contains basic app info (parsed through arguments)
 */
struct s_ctx
{
	// CLI arguments
	long			philos_count;
	long			death_time;
	long			meal_time;
	long			sleep_time;
	long			max_meal_count;
	// Mutexes
	t_mtx			print_mtx;
	t_mtx			ctx_mtx;
	// Forks
	t_fork			*forks;
	// Start time
	long			epoch;
	// Philosophers
	t_philo			*philos;
	// Destruction
	int				philos_created;
	int				philos_launched;
	bool			monitor_launched;
	int				fork_mtx_created;
	bool			ctx_mtx_created;
	bool			print_mtx_created;
	// Mission control
	bool			stop;
	bool			all_threads_ready; // TODO
	int				threads_ready;
};

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
 * @brief Checks if the arguments passed to the app are valid
 *
 * @param argc Arguments count
 * @param argv Arguments count
 * @return bool Whether valid or not
 */
bool				args_check(int argc, char **argv);

/*
 * @brief Parses the cli arguments without checking them
 *
 * @param ctx Context
 * @param argc Cli arguments count
 * @param argc Cli arguments
 */
void				args_parse(t_ctx *ctx, int argc, char **argv);

/**
 * @brief Behavior of a philo eating a meal
 *
 * @param philo Philo
 */
void				eat(t_philo *philo);

/**
 * @brief Frees the app context
 *
 * @param ctx Context
 */
void				free_ctx(t_ctx *ctx);

/**
 * @brief Get the current epoch long of seconds, ms, or us.
 *
 * @param code Enum value of what you want, TIMEE_S, MS or US.
 * @return long Value depending on what we asked for with code
 */
long				get_time(t_time_code code);

/**
 * @brief Initializes the context from the arguments
 *
 * @param argc Arguments count
 * @param argv Arguments
 * @return t_ctx* Context
 */
t_ctx				*init_ctx(int argc, char **argv);

/**
 * @brief Allocates the array for mutextes and initializes each mutex
 * @note In case of failure with any of the following errors, this function
 * frees what it has access to, so ctx with free_ctx and the mutextes with.
 * @throw EAGAIN, ENOMEM, EPERM, EINVAL
 * @see pthread_mutex_destroy(3)
 *
 * @param ctx Context
 * @return true on failure
 * @return false on success otherwise
 */
bool				init_mutexes(t_ctx *ctx);

/**
 * @brief Allocates the array for philosophers
 * @note The array is not NULL-terminated. Use ctx->philos_count
 *
 * @param ctx Context
 * @return false if succeded
 * @return true if failed
 */
bool				init_philos(t_ctx *ctx);

/**
 * @brief Launches philosopher threads to start the simulation.
 *
 * Creates one thread per philosopher, each running the simulation routine.
 * If thread creation fails for any philosopher, the simulation is marked as
 * stopped and the function returns true to indicate failure.
 *
 * @param ctx Pointer to the simulation context.
 * @return true if an error occurred during thread creation, false on success.
 */
bool				launch_philos(t_ctx *ctx);

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
bool				launch_monitor(t_ctx *ctx, pthread_t *big_brother);

/**
 * @brief Logs an action performed by a philosopher.
 *
 * This function prints a timestamped message describing the action taken by
 * the given philosopher. It ensures thread-safe printing using a mutex and
 * does not log anything if the simulation is over.
 *
 * @param philo Pointer to the philosopher structure.
 * @param action Description of the action to log (e.g., "is eating",
 * "is thinking").
 */
bool				log_action(t_philo *philo, const char *action);

/**
 * @brief Gets a value while avoiding data races
 *
 * @param mtx Mutex
 * @param origin Pointer to the value to get
 * @param dest Pointer to where the value will be written.
 *
 * @see Man pthread_mutex_destroy.3
 */
void				mx_gbool(t_mtx *mtx, bool *origin, bool *dest);

/**
 * @brief Sets a boolean value after locking a mutex
 *
 * @param mtx Mutex
 * @param dest Pointer to where the value will be written.
 * @param val Value to set
 *
 * @see Man pthread_mutex_destroy.3
 */
void				mx_sbool(t_mtx *mtx, bool *dest, bool val);

/**
 * @brief Sets a long value after locking a mutex
 *
 * @param mtx Mutex
 * @param dest Pointer to where the value will be written.
 * @param val Value to set
 *
 * @see Man pthread_mutex_destroy.3
 */
void				mx_slong(t_mtx *mtx, long *dest, long val);

/**
 * @brief Increments a long value after locking a mutex
 *
 * @param mtx Mutex
 * @param dest Pointer to where the value will be written.
 *
 * @see Man pthread_mutex_destroy.3
 */
void				mx_ilong(t_mtx *mtx, long *dest);

/**
 * @brief Routine for each thread
 *
 * @param arg Argument
 * @return void* Unused
 */
void				*routine(void *arg);

/**
 * @brief Checks for the death of philosophers
 *
 * @param arg Argument
 * @return void* Unused
 */
void				*routine_monitor(void *arg);

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
void				std_usleep(long milliseconds, t_philo *philo);

/*
 * @brief Loops until all philos are ready or the program should stop
 *
 * @param ctx Context
 */
void				wait_all_philos(t_ctx *ctx);

#endif
