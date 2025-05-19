/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:08:33 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/18 15:22:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** We just strncmp because this is litterally what the function is used for :-)
*/
static bool	is_valid_number_length(char *str)
{
	const char	*max_ulong = "18446744073709551615";
	int			len;

	len = (int)ft_strlen(str);
	if (len > 20)
		return (false);
	if (len == 20)
	{
		if (ft_strcmp(str, max_ulong) > 0)
			return (false);
	}
	return (true);
}

static bool	contains_invalid_chars(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
		{
			write(STDERR_FILENO, FG_RED "Error: '", 13);
			write(STDERR_FILENO, str, ft_strlen(str));
			write(STDERR_FILENO,
				FG_RED "' contains non-numeric characters\n" NC, 38);
			return (false);
		}
		j++;
	}
	return (true);
}

/*
** Checks if a number argument is valid
*/
static bool	is_valid_number(char *str)
{
	if (ft_strlen(str) == 0)
	{
		write(STDERR_FILENO, FG_RED "Error: argument is empty\n" NC, 34);
		return (false);
	}
	if (!contains_invalid_chars(str))
		return (false);
	if (!is_valid_number_length(str))
	{
		write(STDERR_FILENO, FG_RED "Error: '", 13);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, FG_RED "' is out of range for a long integer\n" NC,
			41);
		return (false);
	}
	return (true);
}

bool	args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO,
			FG_YELLOW "Usage: <philos count> <death time> <meal time>", 51);
		write(STDERR_FILENO, " <sleep time> [meals count]\n" NC, 32);
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
