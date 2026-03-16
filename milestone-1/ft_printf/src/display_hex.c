/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:49:28 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 17:53:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long print_hex(int fd, t_format *fmt, unsigned int nbr) {
  long count;

  count = 0;
  if (fmt->hash && nbr != 0) {
    if (fmt->type == 'x')
      count += pfputstr(fd, "0x");
    else
      count += pfputstr(fd, "0X");
  }
  if (fmt->type == 'x')
    count += pfputnbru_base(fd, nbr, BASE_16);
  else
    count += pfputnbru_base(fd, nbr, BASE_16C);
  return (count);
}
