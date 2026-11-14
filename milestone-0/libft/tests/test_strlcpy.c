#include "test.h"

int main(void) {
  char dst[32];

  // Normal copy with plenty of space
  memset(dst, 'X', sizeof(dst));
  size_t ret = ft_strlcpy(dst, "hello", sizeof(dst));
  assert(ret == 5);
  assert(strcmp(dst, "hello") == 0);
  assert(dst[5] == '\0');
  assert(dst[6] == 'X');

  // Exact size fit (including NUL)
  char small[6];
  memset(small, 'X', sizeof(small));
  ret = ft_strlcpy(small, "hello", 6);
  assert(ret == 5);
  assert(strcmp(small, "hello") == 0);

  // Truncation (buffer smaller than string)
  char trunc[4];
  memset(trunc, 'X', sizeof(trunc));
  ret = ft_strlcpy(trunc, "hello", 4);
  assert(ret == 5);
  assert(strcmp(trunc, "hel") == 0);
  assert(trunc[3] == '\0');

  // Size 1 (only NUL written)
  char one[2] = {'A', 'B'};
  ret = ft_strlcpy(one, "hello", 1);
  assert(ret == 5);
  assert(one[0] == '\0');
  assert(one[1] == 'B');

  // Size 0 (destination untouched)
  char untouched[4] = {'A', 'B', 'C', 'D'};
  ret = ft_strlcpy(untouched, "hello", 0);
  assert(ret == 5);
  assert(untouched[0] == 'A');

  return 0;
}
