/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:51:04 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 11:24:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Allocates a 2D matrix of integers.
 *
 * @param	width	The width of the matrix.
 * @param	height	The height of the matrix.
 *
 * @returns	The allocated matrix.
 */
int	**allocate_matrix(int width, int height)
{
	int	**matrix;
	int	i;

	matrix = ft_calloc((unsigned long)height, sizeof(int *));
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < height)
	{
		matrix[i] = ft_calloc((unsigned long)width, sizeof(int));
		if (!matrix[i])
		{
			while (--i >= 0)
				free(matrix[i]);
			free(matrix);
			return (NULL);
		}
		i++;
	}
	return (matrix);
}
