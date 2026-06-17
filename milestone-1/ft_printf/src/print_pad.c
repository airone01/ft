#include "ft_printf.h"

long print_padding(int fd, int current_len, int target_width, char c) {
  long count;

  count = 0;
  while (current_len < target_width) {
    count += pfputchar(fd, c);
    current_len++;
  }
  return (count);
}
