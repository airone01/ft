/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:47:54 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 17:52:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long print_padding(int fd, int current_len, int target_width, char c) {
  long count = 0;
  while (current_len < target_width) {
    count += pfputchar(fd, c);
    current_len++;
  }
  return (count);
}
