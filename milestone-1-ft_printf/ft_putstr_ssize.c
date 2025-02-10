/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_ssize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:28:03 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/10 19:27:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

long	ft_putstr_ssize(char *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	return (write(1, str, (size_t)ft_strlen(str)));
}
