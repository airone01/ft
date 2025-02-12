/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:47:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/13 00:49:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	print_file_error(t_error err)
{
	if (err == ERR_FILE_OPEN)
		ft_printf("%s\n", strerror(errno));
	else if (err == ERR_FILE_READ)
		ft_printf("Failed to read file\n");
	else if (err == ERR_FILE_EXTENSION)
		ft_printf("File must have .fdf extension\n");
	else if (err == ERR_FILE_EMPTY)
		ft_printf("File is empty\n");
}
