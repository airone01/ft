/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:08:33 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 16:09:00 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_bool	args(int argc, char **argv)
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
