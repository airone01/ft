/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_signed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:48:37 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 17:52:49 by elagouch         ###   ########.fr       */
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
      count += pfputchar(fd, '+');
    else if (fmt->space)
      count += pfputchar(fd, ' ');
  }
  count += pfputnbr_base(fd, nbr, BASE_10);
  if (fmt->minus)
    count += print_padding(fd, len, fmt->width, ' ');
  return (count);
}
