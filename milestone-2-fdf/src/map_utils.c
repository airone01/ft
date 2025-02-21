/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:51:04 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 22:28:53 by elagouch         ###   ########.fr       */
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
	int	*data;
	int	i;

	data = ft_calloc((unsigned long)(width * height), sizeof(int));
	matrix = ft_calloc((unsigned long)height, sizeof(int *));
	i = 0;
	while (i < height)
	{
		matrix[i] = &data[i * width];
		i++;
	}
	return (matrix);
}
