/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:09:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 16:01:20 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if the number of digits in the string is valid for an int
 *
 * @param str Argument
 * @return t_bool Whether the length of the number is valid for an int
 */
static t_bool	is_valid_number_length(char *str)
{
	int	len;

	len = (int)ft_strlen(str);
	if (len > 10)
		return (false);
	if (len == 10)
	{
		if (str[0] > '2')
			return (false);
		if (str[0] == '2' && ft_strcmp(str, "2147483647") > 0)
			return (false);
	}
	return (true);
}

/**
 * @brief Checks if the number argument is valid (contains only digits and fits
 * in int range)
 *
 * @param str Argument
 * @return t_bool Whether valid or not
 */
static t_bool	is_valid_number(char *str)
{
	int	j;

	j = 0;
	if (ft_strlen(str) == 0)
	{
		ft_printf_fd(STDERR_FILENO, "Error: argument is empty\n");
		return (false);
	}
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
		{
			ft_printf_fd(STDERR_FILENO,
				"Error: '%s' contains non-numeric characters\n", str);
			return (false);
		}
		j++;
	}
	if (!is_valid_number_length(str))
	{
		ft_printf_fd(STDERR_FILENO,
			"Error: '%s' is out of range for an integer\n", str);
		return (false);
	}
	return (true);
}

/**
 * @brief Checks if the arguments passed to the app are valid
 *
 * @param argc Arguments count
 * @param argv Arguments count
 * @return t_bool Whether valid or not
 */
static t_bool	args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		ft_printf_fd(STDERR_FILENO, "Usage: <philos count> <death time> ");
		ft_printf_fd(STDERR_FILENO, "<meal time> <sleep time> [meals count]\n");
		return (true);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Initializes the context from the arguments
 *
 * @param argc Arguments count
 * @param argv Arguments
 * @return t_ctx* Context
 */
static t_ctx	*init_ctx(int argc, char **argv)
{
	t_ctx	*ctx;

	ctx = ft_calloc(1, sizeof(t_ctx));
	ctx->philos_count = ft_atoi(argv[1]);
	ctx->death_time = ft_atoi(argv[2]);
	ctx->meal_time = ft_atoi(argv[3]);
	ctx->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		ctx->meals_count = ft_atoi(argv[5]);
	return (ctx);
}

/**
 * @brief Main entry to the program
 *
 * @param argc Arguments count
 * @param argv Arguments
 * @return int Return status
 */
int	main(int argc, char **argv)
{
	t_ctx	*ctx;

	if (args(argc, argv))
		return (1);
	ctx = init_ctx(argc, argv);
	ft_printf("test: %d\n", ctx->meal_time);
	return (0);
}
