/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:08:33 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/18 15:22:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The goal of this file is not to parse per say the cli args, but to verify
** them without allocating anything. This is mainly done with strlen and strcmp.
*/

#include "philo.h"
#include "std.h"
#include <unistd.h> // write(), STDERR_FILENO,

/*
** This is just to avoid unreadable code
*/
static void	write_combined_err(const char *s1, const char *s2, const char *s3)
{
	write(STDERR_FILENO, s1, ft_strlen(s1));
	write(STDERR_FILENO, s2, ft_strlen(s2));
	write(STDERR_FILENO, s3, ft_strlen(s3));
}

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
			write_combined_err(FG_RED ERR_COLON "'", str, ERR_NONUM NC);
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
		write(STDERR_FILENO, FG_RED ERR_COLON ERR_NOARG NC, ERR_LEN_BASE + ERR_LEN_NOARG);
		return (false);
	}
	if (!contains_invalid_chars(str))
		return (false);
	if (!is_valid_number_length(str))
	{
		write_combined_err(FG_RED ERR_COLON, str, ERR_RANGE NC);
		return (false);
	}
	return (true);
}

bool	args_check(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, FG_YELLOW ERR_COLON ERR_USAG1 ERR_USAG2 NC,
			ERR_LEN_BASE + ERR_LEN_USAGE);
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
