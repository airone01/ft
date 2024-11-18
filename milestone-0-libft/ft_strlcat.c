/* ************************************************************************** */
/*                                                                            */
/*                                                     _    ⣀⣀⣀⡀⡀⡀⡀⣀⡀⣀⣀⣀⡀  */
/*   ft_strlcat.c                                  _ _/ |   ⡇⣶⡆⡇⡾⢏⡭⡵⠀⡇⣶⡆⡇  */
/*                                                | '_| |_  ⣓⣒⠒⡃⡂⣏⡆⡯⢇⠓⠶⠖⡃  */
/*   By: elagouch <elagouch@student.42.fr>        |_|_|_(@) ⢻⣊⡞⣪⢳⡗⣳⢤⣈⢍⣰⢖⡇  */
/*                                                | | |_  ) ⠜⡲⡢⣲⡯⡼⡑⡁⣝⣘⡚⢠⠅  */
/*   Created: 2024/11/11 15:07:16 by elagouch     |_  _/ /  ⡖⣒⡒⡆⠉⠧⢰⣮⣇⣂⡏⡳⡆  */
/*   Updated: 2024/11/18 10:35:56 by elagouch       |_/___| ⣇⣛⣃⡇⡿⢤⠤⠾⠡⠹⢝⣚⡁  */
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
 * The strlcat() function appends the NUL-terminated string src to the end of
 * dst.  It will append at most size - strlen(dst) - 1 bytes, NUL-terminating the
 * result.
 *
 * @param	dst		destination pointer
 * @param	src		source pointer
 * @param	size	number of characters to copy
 *
 * @returns	pointer to the destination string dst
 */
unsigned int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	i = 0;
	while (size && src[i] && (dst_len + i) < (size - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
