/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <airone01@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:46:40 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 18:23:15 by elagouch         ###   ########.fr       */
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
