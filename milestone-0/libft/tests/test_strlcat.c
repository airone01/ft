#include "test.h"

int main(void) {
  char dst[32];

  // Normal append with space
  strcpy(dst, "hello ");
  size_t ret = ft_strlcat(dst, "world!", sizeof(dst));
  assert(ret == 12);
  assert(strcmp(dst, "hello world!") == 0);

  // Truncation
  char buf[10];
  strcpy(buf, "abc");
  ret = ft_strlcat(buf, "defghij", sizeof(buf)); // 10 total size
  // initial dst len = 3, src len = 7 -> ret = 10
  assert(ret == 10);
  assert(strcmp(buf, "abcdefghi") == 0);
  assert(buf[9] == '\0');

  // Size smaller than or equal to dst len
  char small[10];
  strcpy(small, "12345");
  ret = ft_strlcat(small, "6789", 4);
  // size <= dst_len -> returns size + strlen(src) = 4 + 4 = 8
  assert(ret == 8);
  assert(strcmp(small, "12345") == 0); // small is untouched

  // Size 0
  ret = ft_strlcat(small, "6789", 0);
  assert(ret == 4);

  return 0;
}
