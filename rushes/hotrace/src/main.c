/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:17:13 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/23 23:36:58 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	main(void)
{
	t_list	*tbl[TBL_SIZE];

	ft_bzero(tbl, sizeof(tbl));
	if (process_input(tbl) != 0)
	{
		ft_putendl_fd("Failed to read input", STDERR_FILENO);
		final_countdown(tbl);
		return (1);
	}
	final_countdown(tbl);
	return (0);
}
