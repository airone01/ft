/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_ssize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:28:03 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 16:59:17 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

long	ft_putstr_ssize(int fd, char *str)
{
	if (!str)
		return (write(fd, "(null)", 6));
	return (write(fd, str, (size_t)ft_strlen(str)));
}
