/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:56:34 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 14:45:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>

static long pf_display2(int fd, va_list *args, const char *format) {
  if (*format == 'x')
    return (ft_putnbr_baseu(fd, va_arg(*args, unsigned int), BASE_16));
  else if (*format == 'X')
    return (ft_putnbr_baseu(fd, va_arg(*args, unsigned int), BASE_16C));
  else if (*format == '%')
    return (ft_putchar_ssize(fd, '%'));
  return (0);
}

static long pt_display(int fd, uintptr_t ptr) {
  if (ptr == 0)
    return (ft_putstr_ssize(fd, (char *)"(nil)"));
  return (ft_putstr_ssize(fd, (char *)"0x") +
          ft_putnbr_baseu(fd, ptr, BASE_16));
}

static long pf_display(int fd, va_list *args, const char *format) {
  void *tmp;

  if (*format == 'c')
    return (ft_putchar_ssize(fd, (char)va_arg(*args, int)));
  else if (*format == 's') {
    tmp = va_arg(*args, char *);
    return (ft_putstr_ssize(fd, tmp));
  } else if (*format == 'p')
    return (pt_display(fd, va_arg(*args, uintptr_t)));
  else if (*format == 'd' || *format == 'i')
    return (ft_putnbr_base(fd, va_arg(*args, int), BASE_10));
  else if (*format == 'u')
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

  count = 0;
  va_start(args, format);
  while (*format) {
    if (*format == '%')
      count += pf_display(STDOUT_FILENO, &args, ++format);
    else
      count += ft_putchar_ssize(STDOUT_FILENO, *format);
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

  count = 0;
  va_start(args, format);
  while (*format) {
    if (*format == '%')
      count += pf_display(fd, &args, ++format);
    else
      count += ft_putchar_ssize(fd, *format);
    format++;
  }
  va_end(args);
  return ((int)count);
}
