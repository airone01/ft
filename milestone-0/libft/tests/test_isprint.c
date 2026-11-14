#include "test.h"

int main(void) {
  for (int i = 32; i <= 126; i++) {
    assert(ft_isprint((char)i) == 1);
  }

  assert(ft_isprint(31) == 0);
  assert(ft_isprint(0) == 0);
  assert(ft_isprint(127) == 0);
  assert(ft_isprint('\n') == 0);
  assert(ft_isprint('\t') == 0);
  assert(ft_isprint('\r') == 0);
  return 0;
}
