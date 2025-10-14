/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:46:40 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/16 16:17:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/**
 * Displays "Error\n" to the standard error output
 */
void	std_error(void)
{
	(void)!write(2, "Error\n", 6);
}
