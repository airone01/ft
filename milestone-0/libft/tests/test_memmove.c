#include "test.h"

int main(void) {
  char buf[64] = "abcdefghijklmnopqrstuvwxyz";

  // Non-overlapping
  char dst[64];
  void *ret = ft_memmove(dst, buf, 27);
  assert(ret == dst);
  assert(strcmp(dst, buf) == 0);

  // Overlapping forward (dest > src)
  // "abcdefghij..." copy "abcdefgh" to buf + 2
  // expected: "ababcdefgh..."
  char overlap1[32] = "0123456789";
  ret = ft_memmove(overlap1 + 2, overlap1, 6);
  assert(ret == overlap1 + 2);
  assert(memcmp(overlap1, "0101234589", 10) == 0);

  // Overlapping backward (dest < src)
  char overlap2[32] = "0123456789";
  ret = ft_memmove(overlap2, overlap2 + 2, 6);
  assert(ret == overlap2);
  assert(memcmp(overlap2, "2345676789", 10) == 0);

  // Zero length
  char zero_buf[10] = "hello";
  ret = ft_memmove(zero_buf, "world", 0);
  assert(ret == zero_buf);
  assert(strcmp(zero_buf, "hello") == 0);

  return 0;
}
