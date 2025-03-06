/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:51:04 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/05 13:33:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Allocates a 2D matrix for map points
 *
 * @param width Width of the matrix
 * @param height Height of the matrix
 * @return t_map_point** The allocated matrix or NULL on failure
 */
t_map_point	**allocate_matrix(int width, int height)
{
	t_map_point	**matrix;
	int			i;

	if (width <= 0 || height <= 0)
		return (NULL);
	matrix = ft_calloc((unsigned long)height, sizeof(t_map_point *));
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < height)
	{
		matrix[i] = ft_calloc((unsigned long)width, sizeof(t_map_point));
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
