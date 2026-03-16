/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:56:34 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 17:33:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>

static long pf_display2(int fd, va_list *args, t_format *format) {
  if (format->type == 'x' || format->type == 'X')
    return (print_hex(fd, format, va_arg(*args, unsigned int)));
  else if (format->type == '%')
    return (ft_putchar_ssize(fd, '%'));
  return (0);
}

static long pt_display(int fd, uintptr_t ptr) {
  if (ptr == 0)
    return (ft_putstr_ssize(fd, (char *)"(nil)"));
  return (ft_putstr_ssize(fd, (char *)"0x") +
          ft_putnbr_baseu(fd, ptr, BASE_16));
}

static long pf_display(int fd, va_list *args, t_format *format) {
  if (format->type == 'c')
    return (ft_putchar_ssize(fd, (char)va_arg(*args, int)));
  else if (format->type == 's')
    return (ft_putstr_ssize(fd, va_arg(*args, char *)));
  else if (format->type == 'p')
    return (pt_display(fd, va_arg(*args, uintptr_t)));
  else if (format->type == 'd' || format->type == 'i')
    return (print_signed(fd, format, va_arg(*args, int)));
  else if (format->type == 'u')
    return (ft_putnbr_baseu(fd, va_arg(*args, unsigned int), BASE_10));
  return (pf_display2(fd, args, format));
}

/*
 * @brief Formats and prints a string.
 *
 * @param format The formatting string
 * @param <...> The variables corresponding to the display calls introduced in
 * the formatting string
 *
 * @returns Upon success, the number of characters printed (excluding the
 * ending null byte).
 *
 * @see man printf.3
 */
int ft_printf(const char *format, ...) {
  va_list args;
  long count;
  t_format fmt;

  count = 0;
  va_start(args, format);
  while (*format) {
    if (*format == '%') {
      fmt = parse_format(&format);
      count += pf_display(STDOUT_FILENO, &args, &fmt);
    } else
      count += ft_putchar_ssize(STDOUT_FILENO, *format);
    if (*format)
      format++;
  }
  va_end(args);
  return ((int)count);
}

/*
 * @brief Formats and prints a string.
 *
 * @param format The formatting string
 * @param <...> The variables corresponding to the display calls introduced in
 * the formatting string
 *
 * @returns Upon success, the number of characters printed (excluding the
 * ending null byte).
 *
 * @see man printf.3
 */
int ft_printf_fd(int fd, const char *format, ...) {
  va_list args;
  long count;
  t_format fmt;

  count = 0;
  va_start(args, format);
  while (*format) {
    if (*format == '%') {
      fmt = parse_format(&format);
      count += pf_display(STDOUT_FILENO, &args, &fmt);
    } else
      count += ft_putchar_ssize(fd, *format);
    format++;
  }
  va_end(args);
  return ((int)count);
}
