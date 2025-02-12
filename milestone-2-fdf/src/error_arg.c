/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:47:13 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/13 00:49:26 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	print_arg_error(t_error err)
{
	if (err == ERR_ARG_COUNT)
		ft_printf("Usage: ./fdf <filename>\n");
	else if (err == ERR_ARG_INVALID_FILE)
		ft_printf("Invalid file provided\n");
}
