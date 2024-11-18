/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:53:03 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/02 17:47:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Frees a pointer and returns NULL.
 *
 * @param	ptr	pointer to free
 *
 * @returns	NULL
 */
void	*free_and_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

#include <stdio.h>

/*
 * Frees a pointer and returns NULL.
 *
 * @param	ptr1	pointer to free
 * @param	ptr2	pointer to free
 *
 * @returns	NULL
 */
void	*free_and_null_map(void *ptr, t_tile **map, t_coords coords)
{
	free(ptr);
	bsq_map_free(map, coords);
	return (NULL);
}

/*
 * Frees an array of strings.
 *
 * @param	strs	array of strings
 */
void	free_strs(char **strs)
{
	while (*strs != NULL)
	{
		free(*strs);
		strs++;
	}
}
