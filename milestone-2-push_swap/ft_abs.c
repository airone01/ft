/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:40:32 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 18:42:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/**
 * Gets the absolute value
 * @param   nb  Number to get the absolute value of
 * @return      Absolute value of nb
 */
ssize_t ft_abs(ssize_t nb)
{
    if (nb < 0)
        return (-nb);
    return (nb);
}
