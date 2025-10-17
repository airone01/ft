/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:25:49 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 15:19:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

bool	config_line_condition(char *trimmed)
{
	return (!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "SO ", 3)
		|| !ft_strncmp(trimmed, "WE ", 3) || !ft_strncmp(trimmed, "EA ", 3)
		|| !ft_strncmp(trimmed, "D ", 2) || !ft_strncmp(trimmed, "P ", 2)
		|| !ft_strncmp(trimmed, "F ", 2) || !ft_strncmp(trimmed, "C ", 2));
}
