#include "test.h"

int main(void) {
  assert(ft_toupper('a') == 'A');
  assert(ft_toupper('z') == 'Z');
  assert(ft_toupper('m') == 'M');
  assert(ft_toupper('A') == 'A');
  assert(ft_toupper('Z') == 'Z');
  assert(ft_toupper('0') == '0');
  assert(ft_toupper('!') == '!');
  assert(ft_toupper('\0') == '\0');
  return 0;
}
