/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 08:17:50 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/01 08:22:26 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Infers a number from a string.
 *
 * @param	str	string to infer number from
 *
 * @returns	infered number
 * @returns	0 if failed (or if there was no number)
 *
 * Execution:
 * 1. Skip spaces
 * 2. Skip `+` and registers _at most_ 1 `-` for negative numbers
 * 3. Registers the number digit by digit until any non-decimal char is found
 * 4. Skips the rest of the string
 *
 * Caveats:
 * - Ignores only white spaces first, then only `+`
 * - Doesn't handle multi-negation
 * - Not "smart"
 */
int	ft_atoi(char *str)
{
	int	count;
	int	mult;

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
