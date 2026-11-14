#include "test.h"

int main(void) {
  char src[32] = "Testing memcpy function!";
  char dst[32];
  memset(dst, 0, sizeof(dst));

  void *ret = ft_memcpy(dst, src, strlen(src) + 1);
  assert(ret == dst);
  assert(strcmp(dst, src) == 0);

  // Partial copy
  char dst2[16];
  memset(dst2, 'X', sizeof(dst2));
  ret = ft_memcpy(dst2, "12345", 5);
  assert(ret == dst2);
  assert(memcmp(dst2, "12345", 5) == 0);
  assert(dst2[5] == 'X');

  // Zero-byte copy
  ret = ft_memcpy(dst2, "abc", 0);
  assert(ret == dst2);
  assert(dst2[0] == '1');

  return 0;
}
