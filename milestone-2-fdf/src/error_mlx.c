/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:48:30 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 10:31:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_mlx_error(t_error err)
{
	if (err == ERR_MLX_INIT)
		ft_printf("Failed to initialize MLX\n");
	else if (err == ERR_MLX_WINDOW)
		ft_printf("Failed to create window\n");
	else if (err == ERR_MLX_IMAGE)
		ft_printf("Failed to create image\n");
}
