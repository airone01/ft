/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:48:52 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/13 00:49:01 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	print_math_error(t_error err)
{
	if (err == ERR_MATRIX_OVERFLOW)
		ft_printf("Matrix calculation overflow\n");
	else if (err == ERR_INVALID_ROTATION)
		ft_printf("Invalid rotation value\n");
	else if (err == ERR_INVALID_SCALE)
		ft_printf("Invalid scale value\n");
	else if (err == ERR_INVALID_PROJECTION)
		ft_printf("Invalid projection type\n");
}
