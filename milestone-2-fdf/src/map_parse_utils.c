/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:22:42 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 17:29:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_bool	count_columns_in_line_loop(const char **ptr, t_bool *in_number,
		int *col)
{
	if (ft_isspace(**ptr))
	{
		if (*in_number)
			*in_number = false;
		*ptr += 1;
		return (true);
	}
	if (!*in_number)
	{
		*in_number = true;
		*col += 1;
	}
	return (false);
}

int	count_columns_in_line(const char *line)
{
	const char	*ptr;
	t_bool		in_number;
	int			col;

	col = 0;
	ptr = line;
	in_number = false;
	if (!line)
		return (0);
	while (*ptr)
	{
		if (count_columns_in_line_loop((const char **)&ptr, &in_number, &col))
			continue ;
		ptr++;
	}
	return (col);
}
