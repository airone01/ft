#include "test.h"

int main(void) {
  for (char c = '0'; c <= '9'; c++) {
    assert(ft_isdigit(c) == 1);
  }

  assert(ft_isdigit('0' - 1) == 0);
  assert(ft_isdigit('9' + 1) == 0);
  assert(ft_isdigit('a') == 0);
  assert(ft_isdigit('Z') == 0);
  assert(ft_isdigit(' ') == 0);
  assert(ft_isdigit('\0') == 0);
  assert(ft_isdigit('-') == 0);
  assert(ft_isdigit('+') == 0);
  return 0;
}
