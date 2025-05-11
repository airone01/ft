/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:08:33 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 13:29:26 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static bool	is_valid_number(char *str)
{
	int	j;

	j = 0;
	if (ft_strlen(str) == 0)
	{
		printf("Error: argument is empty\n");
		return (false);
	}
	while (str[j])
	{
		if (!ft_isdigit(str[j]))
		{
			printf("Error: '%s' contains non-numeric characters\n", str);
			return (false);
		}
		j++;
	}
	if (!is_valid_number_length(str))
	{
		printf("Error: '%s' is out of range for a long integer\n", str);
		return (false);
	}
	return (true);
}

bool	args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: <philos count> <death time> ");
		printf("<meal time> <sleep time> [meals count]\n");
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
