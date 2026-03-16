/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:31:59 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 18:32:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>

long print_string(int fd, t_format *fmt, const char *str) {
  long count;
  int len;

  count = 0;
  if (!str)
    str = "(null)";
  len = (int)ft_strlen(str);
  if (fmt->precision >= 0 && fmt->precision < len)
    len = fmt->precision;
  if (!fmt->minus)
    count += print_padding(fd, len, fmt->width, ' ');
  count += write(fd, str, (size_t)len);
  if (fmt->minus)
    count += print_padding(fd, len, fmt->width, ' ');
  return (count);
}
