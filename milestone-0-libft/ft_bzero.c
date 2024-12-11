/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 17:59:43 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The  bzero()  function erases the data in the n bytes of the memory starting
 * at the location pointed to by s, by writing zeros (bytes containing '\0') to
 * that area.
 * @param	s	Pointer
 * @param	n	Size in number of bytes
 * @returns	pointer to the memory area s
 */
void	*ft_bzero(void *s, size_t n)
{
	return (ft_memset(s, 0, n));
}
