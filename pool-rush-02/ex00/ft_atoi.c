/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:08:18 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/28 11:20:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Converts string of a number to a long.
 * A bit better than the actual atoi: handles "-"
 * more than once.
 */
long	ft_atoi(char *str)
{
	long	count;
	long	mult;

	count = 0;
	mult = 1;
	while ((*str >= 8 && *str <= 13) || *str == ' ')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			mult = -mult;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		count = (count * 10) + (*str - '0');
		str++;
	}
	return (mult * count);
}
