/* ************************************************************************** */
/*                                                                            */
/*                                                     _    ⣀⣀⣀⡀⡀⡀⡀⣀⡀⣀⣀⣀⡀  */
/*   ft_memchr.c                                   _ _/ |   ⡇⣶⡆⡇⡾⢏⡭⡵⠀⡇⣶⡆⡇  */
/*                                                | '_| |_  ⣓⣒⠒⡃⡂⣏⡆⡯⢇⠓⠶⠖⡃  */
/*   By: elagouch <elagouch@student.42lyon.fr>    |_|_|_(@) ⢻⣊⡞⣪⢳⡗⣳⢤⣈⢍⣰⢖⡇  */
/*                                                | | |_  ) ⠜⡲⡢⣲⡯⡼⡑⡁⣝⣘⡚⢠⠅  */
/*   Created: 2024/11/11 16:41:27 by elagouch     |_  _/ /  ⡖⣒⡒⡆⠉⠧⢰⣮⣇⣂⡏⡳⡆  */
/*   Updated: 2024/11/11 16:53:12 by elagouch       |_/___| ⣇⣛⣃⡇⡿⢤⠤⠾⠡⠹⢝⣚⡁  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * The  memchr()  function scans the initial n bytes of the memory area pointed
 * to by s for the first instance of c.  Both c and the  bytes  of  the  memory
 * area pointed to by s are interpreted as uint8_t.
 *
 * @param	s	haystack
 * @param	c	needle
 * @param	n	max bytes to scan
 *
 * @returns	pointer to the matching byte or NULL if the character does not occur
 * in the given memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	uint8_t	*se;

	se = (uint8_t *)s;
	while (n--)
	{
		if (*se == (uint8_t)c)
			return (se);
		se++;
	}
	return (0);
}
