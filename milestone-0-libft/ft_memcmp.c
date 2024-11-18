/* ************************************************************************** */
/*                                                                            */
/*                                                     _    ⣀⣀⣀⡀⡀⡀⡀⣀⡀⣀⣀⣀⡀  */
/*   ft_memcmp.c                                   _ _/ |   ⡇⣶⡆⡇⡾⢏⡭⡵⠀⡇⣶⡆⡇  */
/*                                                | '_| |_  ⣓⣒⠒⡃⡂⣏⡆⡯⢇⠓⠶⠖⡃  */
/*   By: elagouch <elagouch@student.42lyon.fr>    |_|_|_(@) ⢻⣊⡞⣪⢳⡗⣳⢤⣈⢍⣰⢖⡇  */
/*                                                | | |_  ) ⠜⡲⡢⣲⡯⡼⡑⡁⣝⣘⡚⢠⠅  */
/*   Created: 2024/11/11 16:41:27 by elagouch     |_  _/ /  ⡖⣒⡒⡆⠉⠧⢰⣮⣇⣂⡏⡳⡆  */
/*   Updated: 2024/11/11 17:09:07 by elagouch       |_/___| ⣇⣛⣃⡇⡿⢤⠤⠾⠡⠹⢝⣚⡁  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * The  memcmp()  function  compares the first n bytes (each interpreted as un‐
 * signed char) of the memory areas s1 and s2.
 *
 * @paran	s1	first string
 * @param	s2	second string
 * @param	n	max bytes to compare
 *
 * @returns	See below
 *
 * The memcmp() function returns an integer less than,  equal  to,  or  greater
 * than  zero  if  the  first  n bytes of s1 is found, respectively, to be less
 * than, to match, or be greater than the first n bytes of s2.
 *
 * For a nonzero return value, the sign is determined by the sign of  the  dif‐
 * ference  between the first pair of bytes (interpreted as uint8_t) that
 * differ in s1 and s2.
 *
 * If n is zero, the return value is zero.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	uint8_t	*se1;
	uint8_t	*se2;
	size_t	i;

	if (n == 0)
		return (0);
	se1 = (uint8_t *)s1;
	se2 = (uint8_t *)s2;
	i = 0;
	while (n--)
	{
		if (se1[i] != se2[i])
			return ((uint8_t) se1[i] - (uint8_t) se2[i]);
		i++;
	}
	return (0);
}
