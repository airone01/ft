/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:11:15 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/02 19:38:08 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

t_map	*read_map_from_argv(int *len, char *str)
{
	t_map	*map;

	*len = bsq_map_file_size(str);
	if (*len == -1)
	{
		ft_puterr("map error\n");
		return (NULL);
	}
	map = bsq_map_read(str, *len);
	return (map);
}

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_map	*map;
	int		len;
	int		i;

	i = 1;
	while (i < argc || (argc == 1 && i == 1))
	{
		if (argc == 1)
			map = bsq_map_stdin_read(2048);
		else
			map = read_map_from_argv(&len, argv[i]);
		if (map == NULL)
		{
			ft_puterr("map error\n");
			bsq_smap_free(map);
			break ;
		}
		bsq_solve(*map);
		bsq_map_put(*map);
		bsq_smap_free(map);
		i++;
	}
}
