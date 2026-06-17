#include "ft_printf_bonus.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

static long pf_display2(int fd, va_list *args, t_format *format) {
  if (format->type == 'x' || format->type == 'X')
    return (print_hex(fd, format, va_arg(*args, unsigned int)));
  else if (format->type == '%')
    return (pfputchar(fd, '%'));
  return (0);
}

static long pf_display(int fd, va_list *args, t_format *format) {
  if (format->type == 'c')
    return (print_char(fd, format, (char)va_arg(*args, int)));
  else if (format->type == 's')
    return (print_string(fd, format, va_arg(*args, const char *)));
  else if (format->type == 'p')
    return (print_pointer(fd, format, va_arg(*args, uintptr_t)));
  else if (format->type == 'd' || format->type == 'i')
    return (print_signed(fd, format, va_arg(*args, int)));
  else if (format->type == 'u')
    return (print_unsigned(fd, format, va_arg(*args, unsigned int)));
  return (pf_display2(fd, args, format));
}

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
      count += pfputchar(STDOUT_FILENO, *format);
    if (*format)
      format++;
  }
  va_end(args);
  return ((int)count);
}

int ft_printf_fd(int fd, const char *format, ...) {
  va_list args;
  long count;
  t_format fmt;

  count = 0;
  va_start(args, format);
  while (*format) {
    if (*format == '%') {
      fmt = parse_format(&format);
      count += pf_display(fd, &args, &fmt);
    } else
      count += pfputchar(fd, *format);
    format++;
  }
  va_end(args);
  return ((int)count);
}
