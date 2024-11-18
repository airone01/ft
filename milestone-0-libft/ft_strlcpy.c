/* ************************************************************************** */
/*                                                                            */
/*                                                     _    ⣀⣀⣀⡀⡀⡀⡀⣀⡀⣀⣀⣀⡀  */
/*   ft_strlcpy.c                                  _ _/ |   ⡇⣶⡆⡇⡾⢏⡭⡵⠀⡇⣶⡆⡇  */
/*                                                | '_| |_  ⣓⣒⠒⡃⡂⣏⡆⡯⢇⠓⠶⠖⡃  */
/*   By: elagouch <elagouch@student.42lyon.fr>    |_|_|_(@) ⢻⣊⡞⣪⢳⡗⣳⢤⣈⢍⣰⢖⡇  */
/*                                                | | |_  ) ⠜⡲⡢⣲⡯⡼⡑⡁⣝⣘⡚⢠⠅  */
/*   Created: 2024/11/11 14:26:39 by elagouch     |_  _/ /  ⡖⣒⡒⡆⠉⠧⢰⣮⣇⣂⡏⡳⡆  */
/*   Updated: 2024/11/12 09:32:54 by elagouch       |_/___| ⣇⣛⣃⡇⡿⢤⠤⠾⠡⠹⢝⣚⡁  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * The strlcpy() and strlcat() functions copy and concatenate strings respec‐
 * tively.  They are designed to be safer, more consistent, and less error prone
 * replacements for strncpy(3) and strncat(3).  Unlike those functions, strlcpy()
 * and strlcat() take the full size of the buffer (not just the length) and guar‐
 * antee to NUL-terminate the result (as long as size is larger than 0 or, in the
 * case of strlcat(), as long as there is at least one byte free in dst).  Note
 * that a byte for the NUL should be included in size.  Also note that strlcpy()
 * and strlcat() only operate on true “C” strings.  This means that for strlcpy()
 * src must be NUL-terminated and for strlcat() both src and dst must be NUL-ter‐
 * minated.
 *
 * The strlcpy() function copies up to size - 1 characters from the NUL-termi‐
 * nated string src to dst, NUL-terminating the result.
 *
 * @param	dest	destination pointer
 * @param	src		source pointer
 * @param	size	number of characters to copy
 *
 * @returns	total length of the string the function tried to create
 */
unsigned int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	if (size == 0)
		return (i);
	size--;
	while (size-- && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (i);
}
