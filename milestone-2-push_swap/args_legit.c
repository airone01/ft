/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_legit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:52:59 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/07 18:36:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Checks if the args passed to the app are correct
 * @param   argc    Arguments count
 * @param   argv    Arguments
 * @return          Boolean result
 */
size_t	args_legit(int argc, char **argv)
{
	char	*str;

	while (argc--)
	{
		str = *argv;
		while (*str == ' ' || (*str >= 7 && *str <= 15))
			str++;
		if (*str == '+' || *str == '-')
			str++;
		if (!*str || !ft_isdigit(*str))
			return (0);
		while (*str)
		{
			if (!ft_isdigit(*str) && !(*str == ' ' || (*str >= 7 && *str <= 15))
				&& !(*str == '+' || *str == '-'))
				return (0);
			str++;
		}
		argv++;
	}
	return (1);
}
