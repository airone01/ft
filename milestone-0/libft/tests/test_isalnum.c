#include "test.h"

int main(void) {
  for (char c = '0'; c <= '9'; c++) {
    assert(ft_isalnum(c) == 1);
  }
  for (char c = 'a'; c <= 'z'; c++) {
    assert(ft_isalnum(c) == 1);
  }
  for (char c = 'A'; c <= 'Z'; c++) {
    assert(ft_isalnum(c) == 1);
  }

  assert(ft_isalnum(' ') == 0);
  assert(ft_isalnum('!') == 0);
  assert(ft_isalnum('@') == 0);
  assert(ft_isalnum('\0') == 0);
  assert(ft_isalnum('\t') == 0);
  assert(ft_isalnum(127) == 0);
  return 0;
}
