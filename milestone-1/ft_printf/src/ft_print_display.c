/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:31:59 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 17:40:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int pfget_num_len(long nbr) {
  int len = 0;
  if (nbr == 0)
    return (1);
  if (nbr < 0) {
    len++;
    nbr = -nbr;
  }
  while (nbr > 0) {
    len++;
    nbr /= 10;
  }
  return (len);
}

static long print_padding(int fd, int current_len, int target_width, char c) {
  long count = 0;
  while (current_len < target_width) {
    count += ft_putchar_ssize(fd, c);
    current_len++;
  }
  return (count);
}

long print_hex(int fd, t_format *fmt, unsigned int nbr) {
  long count;

  count = 0;
  if (fmt->hash && nbr != 0) {
    if (fmt->type == 'x')
      count += ft_putstr_ssize(fd, "0x");
    else
      count += ft_putstr_ssize(fd, "0X");
  }
  if (fmt->type == 'x')
    count += ft_putnbr_baseu(fd, nbr, BASE_16);
  else
    count += ft_putnbr_baseu(fd, nbr, BASE_16C);
  return (count);
}

long print_signed(int fd, t_format *fmt, int nbr) {
  long count;
  int len;

  count = 0;
  len = pfget_num_len(nbr);
  if (nbr >= 0 && (fmt->plus || fmt->space))
    len++;
  if (!fmt->minus)
    count += print_padding(fd, len, fmt->width, ' ');
  if (nbr >= 0) {
    if (fmt->plus)
      count += ft_putchar_ssize(fd, '+');
    else if (fmt->space)
      count += ft_putchar_ssize(fd, ' ');
  }
  count += ft_putnbr_base(fd, nbr, BASE_10);
  if (fmt->minus)
    count += print_padding(fd, len, fmt->width, ' ');
  return (count);
}
