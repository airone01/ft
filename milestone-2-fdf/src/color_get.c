/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:35:15 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/20 16:56:20 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Get a color based on the average of two z values
 *
 * @param	z1	First z value
 * @param	z2	Second z value
 *
 * @returns	unsigned int	Color value
 */
unsigned int	color_get(int z1, int z2)
{
	int	avg_z;

	avg_z = (z1 + z2) / 2;
	if (avg_z > 125)
		return (0x00FF0000);
	else if (avg_z > 0)
		return (0x0000FF00);
	else
		return (0x000000FF);
}
