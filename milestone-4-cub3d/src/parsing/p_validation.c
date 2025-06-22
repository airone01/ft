/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_validation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:50:56 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 13:39:58 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

/*
** `p_validation_pproc.c`
*/
bool	check_bonus_textures(t_data *data);

bool	check_texture_completeness(t_data *data)
{
	if (!data->texture_n)
	{
		ft_printf(RED "Error\nMissing North texture (NO)\n" RESET);
		return (true);
	}
	if (!data->texture_s)
	{
		ft_printf(RED "Error\nMissing South texture (SO)\n" RESET);
		return (true);
	}
	if (!data->texture_e)
	{
		ft_printf(RED "Error\nMissing East texture (EA)\n" RESET);
		return (true);
	}
	if (!data->texture_w)
	{
		ft_printf(RED "Error\nMissing West texture (WE)\n" RESET);
		return (true);
	}
	return (check_bonus_textures(data));
}

bool	check_color_completeness(t_data *data)
{
	if (data->floor_color.red < 0 || data->floor_color.red > 255)
	{
		ft_printf(RED "Error\nInvalid floor color configuration\n" RESET);
		return (true);
	}
	if (data->ceil_color.red < 0 || data->ceil_color.red > 255)
	{
		ft_printf(RED "Error\nInvalid ceiling color configuration\n" RESET);
		return (true);
	}
	return (false);
}

bool	validate_config_completeness(t_data *data)
{
	if (!data)
	{
		ft_printf(RED "Error\nInvalid data structure\n" RESET);
		return (true);
	}
	if (check_texture_completeness(data))
		return (true);
	if (check_color_completeness(data))
		return (true);
	if (!data->map || data->map_height <= 0 || data->map_width <= 0)
	{
		ft_printf(RED "Error\nInvalid or missing map\n" RESET);
		return (true);
	}
	return (false);
}
