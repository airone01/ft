/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:48:14 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/13 00:50:03 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	print_map_error(t_error err)
{
	if (err == ERR_MAP_INVALID_CHAR)
		ft_printf("Invalid character in map\n");
	else if (err == ERR_MAP_IRREGULAR)
		ft_printf("Map must be rectangular\n");
	else if (err == ERR_MAP_TOO_LARGE)
		ft_printf("Map is too large\n");
	else if (err == ERR_MAP_EMPTY_LINE)
		ft_printf("Empty line in map\n");
	else if (err == ERR_MAP_INVALID_COLOR)
		ft_printf("Invalid color format\n");
}
