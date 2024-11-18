/* ************************************************************************** */
/*                                                                            */
/*                                                     _    ⣀⣀⣀⡀⡀⡀⡀⣀⡀⣀⣀⣀⡀  */
/*   ft_calloc.c                                   _ _/ |   ⡇⣶⡆⡇⡾⢏⡭⡵⠀⡇⣶⡆⡇  */
/*                                                | '_| |_  ⣓⣒⠒⡃⡂⣏⡆⡯⢇⠓⠶⠖⡃  */
/*   By: elagouch <elagouch@student.42lyon.fr>    |_|_|_(@) ⢻⣊⡞⣪⢳⡗⣳⢤⣈⢍⣰⢖⡇  */
/*                                                | | |_  ) ⠜⡲⡢⣲⡯⡼⡑⡁⣝⣘⡚⢠⠅  */
/*   Created: 2024/11/11 18:23:11 by elagouch     |_  _/ /  ⡖⣒⡒⡆⠉⠧⢰⣮⣇⣂⡏⡳⡆  */
/*   Updated: 2024/11/11 18:56:22 by elagouch       |_/___| ⣇⣛⣃⡇⡿⢤⠤⠾⠡⠹⢝⣚⡁  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * The calloc() function allocates memory for an array  of  nmemb  elements  of
 * size  bytes  each and returns a pointer to the allocated memory.  The memory
 * is set to zero.  If nmemb or size is 0, then calloc() returns  either  NULL,
 * or  a  unique pointer value that can later be successfully passed to free().
 * If the multiplication of nmemb and size would result  in  integer  overflow,
 * then  calloc() returns an error.  By contrast, an integer overflow would not
 * be detected in the following call to malloc(), with the result that  an  in‐
 * correctly sized block of memory would be allocated:
 *
 * ```c
 * malloc(nmemb * size);
 * ```
 *
 * @param	nmemb	length of the variable
 * @param	size	length of the type of the variable
 *
 * @returns	pointer filled with NUL
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && nmemb > SIZE_MAX / size)
		return (0);
	ptr = malloc(size * nmemb);
	if (!ptr)
		return (0);
	return (ft_bzero(ptr, size * nmemb));
}
