/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:16:24 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/13 00:23:44 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	args_check(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
		exit_error(NULL, ERR_ARG_COUNT);
}
