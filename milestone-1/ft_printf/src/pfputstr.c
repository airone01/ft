/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfputstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:28:03 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 17:55:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

long pfputstr(int fd, const char *str) {
  if (!str)
    return (write(fd, "(null)", 6));
  return (write(fd, str, (size_t)ft_strlen(str)));
}
