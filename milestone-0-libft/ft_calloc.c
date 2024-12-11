/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 17:59:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The calloc() function allocates memory for an array  of  nmemb  elements  of
 * size  bytes  each and returns a pointer to the allocated memory.  The memory
 * is set to zero.  If nmemb or size is 0, then calloc() returns  either  NULL,
 * or  a  unique pointer value that can later be successfully passed to free().
 * If the multiplication of nmemb and size would result  in  integer  overflow,
 * then  calloc() returns an error.  By contrast, an integer overflow would not
 * be detected in the following call to malloc(), with the result that  an  in‐
 * correctly sized block of memory would be allocated:
 * ```c
 * malloc(nmemb * size);
 * ```
 * @param	nmemb	Length of the variable
 * @param	size	Length of the type of the variable
 * @returns	pointer Filled with NUL
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
