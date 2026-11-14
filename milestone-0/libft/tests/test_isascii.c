#include "test.h"

int main(void) {
  for (int i = 0; i <= 127; i++) {
    assert(ft_isascii((char)i) == 1);
  }
  assert(ft_isascii((char)128) == 0);
  assert(ft_isascii((char)255) == 0);
  assert(ft_isascii((char)-1) == 0);
  return 0;
}
