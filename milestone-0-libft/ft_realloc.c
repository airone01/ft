/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:04:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 22:11:06 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Reallocates a memory block.
 *
 * @param	ptr			The pointer to the memory block to reallocate.
 * @param	old_size	The old size of the memory block.
 * @param	new_size	The new size of the memory block.
 *
 * @returns	The reallocated memory block.
 */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, (size_t)ft_min((long)old_size, (long)new_size));
		free(ptr);
	}
	return (new_ptr);
}
