#include "test.h"

int main(void) {
  assert(ft_memcmp("abc", "abc", 3) == 0);
  assert(ft_memcmp("abc", "abd", 2) == 0);
  assert(ft_memcmp("abc", "abd", 3) < 0);
  assert(ft_memcmp("abd", "abc", 3) > 0);
  assert(ft_memcmp("abc", "xyz", 0) == 0);

  // Embedded NUL bytes
  char m1[5] = {'a', '\0', 'b', 'c', 'd'};
  char m2[5] = {'a', '\0', 'b', 'c', 'd'};
  char m3[5] = {'a', '\0', 'b', 'x', 'd'};
  assert(ft_memcmp(m1, m2, 5) == 0);
  assert(ft_memcmp(m1, m3, 3) == 0);
  assert(ft_memcmp(m1, m3, 4) < 0);

  // Unsigned char comparison
  unsigned char b1[1] = {0xFF};
  unsigned char b2[1] = {0x00};
  assert(ft_memcmp(b1, b2, 1) > 0);

  return 0;
}
