#include "test.h"

int main(void) {
  assert(ft_strncmp("abc", "abc", 3) == 0);
  assert(ft_strncmp("abc", "abc", 5) == 0);
  assert(ft_strncmp("abc", "abd", 2) == 0);
  assert(ft_strncmp("abc", "abd", 3) < 0);
  assert(ft_strncmp("abd", "abc", 3) > 0);
  assert(ft_strncmp("abc", "abcdef", 3) == 0);
  assert(ft_strncmp("abc", "abcdef", 4) < 0);
  assert(ft_strncmp("abcdef", "abc", 4) > 0);
  assert(ft_strncmp("", "", 1) == 0);
  assert(ft_strncmp("abc", "xyz", 0) == 0);

  // Unsigned char comparison test (\xff > \x01)
  assert(ft_strncmp("\xff", "\x01", 1) > 0);

  return 0;
}
