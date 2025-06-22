/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_color_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:39:34 by maximart          #+#    #+#             */
/*   Updated: 2025/06/20 19:33:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static bool	check_comma_count(t_data *data, int count_comma)
{
	if (count_comma != 2)
	{
		data->error_detected = true;
		ft_printf(RED "Error\nColor values must be like "
			"[0-255],[0-255],[0-255]\n" RESET);
		return (true);
	}
	return (false);
}

bool	check_color_line(t_data *data, char *color)
{
	char	*check;
	int		count_comma;

	count_comma = 0;
	check = color;
	while (*check)
	{
		if (*check == ',')
			count_comma++;
		if (!ft_isdigit(*check) && *check != ',' && *check != '\n')
		{
			ft_printf(RED "Error\nColor values must be like "
				"[0-255],[0-255],[0-255]\n" RESET);
			data->error_detected = true;
			return (true);
		}
		check++;
	}
	if (check_comma_count(data, count_comma))
		return (true);
	return (false);
}
