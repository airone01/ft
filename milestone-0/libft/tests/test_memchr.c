#include "test.h"

int main(void) {
  const char mem[] = "abcdef\0ghijk";

  assert(ft_memchr(mem, 'a', 12) == mem);
  assert(ft_memchr(mem, 'c', 12) == mem + 2);
  assert(ft_memchr(mem, '\0', 12) == mem + 6);
  assert(ft_memchr(mem, 'g', 12) == mem + 7);
  assert(ft_memchr(mem, 'k', 12) == mem + 11);

  // Exceeding n
  assert(ft_memchr(mem, 'c', 2) == NULL);
  assert(ft_memchr(mem, 'z', 12) == NULL);
  assert(ft_memchr(mem, 'a', 0) == NULL);

  // Unsigned byte match
  unsigned char raw[4] = {0x10, 0xFE, 0x80, 0x00};
  assert(ft_memchr(raw, 0xFE, 4) == raw + 1);

  return 0;
}
