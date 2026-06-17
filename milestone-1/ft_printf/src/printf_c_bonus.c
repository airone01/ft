#include "ft_printf_bonus.h"

long print_char(int fd, t_format *fmt, char c) {
  long count;

  count = 0;
  if (!fmt->minus)
    count += print_padding(fd, 1, fmt->width, ' ');
  count += pfputchar(fd, c);
  if (fmt->minus)
    count += print_padding(fd, 1, fmt->width, ' ');
  return (count);
}

static int get_hexlen_ptr(uintptr_t n) {
  int len;

  len = 0;
  if (n == 0)
    return (1);
  while (n > 0) {
    len++;
    n /= 16;
  }
  return (len);
}

long print_pointer(int fd, t_format *fmt, uintptr_t ptr) {
  long count;
  int len;

  count = 0;
  if (ptr == 0) {
    len = 5;
    if (!fmt->minus)
      count += print_padding(fd, len, fmt->width, ' ');
    count += pfputstr(fd, "(nil)");
    if (fmt->minus)
      count += print_padding(fd, len, fmt->width, ' ');
    return (count);
  }
  len = 2 + get_hexlen_ptr(ptr);
  if (!fmt->minus)
    count += print_padding(fd, len, fmt->width, ' ');
  count += pfputstr(fd, "0x");
  count += pfputnbru_base(fd, ptr, BASE_16);
  if (fmt->minus)
    count += print_padding(fd, len, fmt->width, ' ');
  return (count);
}
