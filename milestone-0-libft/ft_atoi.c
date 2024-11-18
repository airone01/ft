/* ************************************************************************** */
/*                                                                            */
/*                                                     _    ⣀⣀⣀⡀⡀⡀⡀⣀⡀⣀⣀⣀⡀  */
/*   ft_atoi.c                                     _ _/ |   ⡇⣶⡆⡇⡾⢏⡭⡵⠀⡇⣶⡆⡇  */
/*                                                | '_| |_  ⣓⣒⠒⡃⡂⣏⡆⡯⢇⠓⠶⠖⡃  */
/*   By: elagouch <elagouch@student.42lyon.fr>    |_|_|_(@) ⢻⣊⡞⣪⢳⡗⣳⢤⣈⢍⣰⢖⡇  */
/*                                                | | |_  ) ⠜⡲⡢⣲⡯⡼⡑⡁⣝⣘⡚⢠⠅  */
/*   Created: 2024/11/11 17:21:41 by elagouch     |_  _/ /  ⡖⣒⡒⡆⠉⠧⢰⣮⣇⣂⡏⡳⡆  */
/*   Updated: 2024/11/11 18:19:02 by elagouch       |_/___| ⣇⣛⣃⡇⡿⢤⠤⠾⠡⠹⢝⣚⡁  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Checks if the result is an overflow.
*/
static int	is_overflow(long long result, int b)
{
	if ((result > LLONG_MAX / 10)
		|| (result == LLONG_MAX / 10 && b > LLONG_MAX % 10))
		return (1);
	return (0);
}

/*
 * Classical atol implementation.
*/
long	ft_atol(const char *nptr)
{
	unsigned long	count;
	int				mult;

	count = 0;
	mult = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			mult *= -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (is_overflow(count, *nptr - '0'))
			return (-1);
		count = (count * 10) + (*nptr++ - '0');
	}
	return (mult * count);
}

/*
 * Infers a number from a sing.
 *
 * @param	nptr	sing to infer number from
 *
 * @returns	infered number
 * @returns	0 if failed (or if there was no number)
 *
 * Execution:
 * 1. Skip spaces
 * 2. Skip `+` and registers _at most_ 1 `-` for negative numbers
 * 3. Registers the number digit by digit until any non-decimal char is found
 * 4. Skips the rest of the sing
 *
 * Caveats:
 * - Ignores only white spaces first, then only `+`
 * - Doesn't handle multi-negation
 * - Not "smart"
 */
int	ft_atoi(const char *nptr)
{
	return (ft_atol(nptr));
}
