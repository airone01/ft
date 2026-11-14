#include "test.h"

int main(void) {
  assert(ft_isalpha('a') == 1);
  assert(ft_isalpha('z') == 1);
  assert(ft_isalpha('A') == 1);
  assert(ft_isalpha('Z') == 1);
  assert(ft_isalpha('m') == 1);
  assert(ft_isalpha('M') == 1);

  assert(ft_isalpha('0') == 0);
  assert(ft_isalpha('9') == 0);
  assert(ft_isalpha(' ') == 0);
  assert(ft_isalpha('-') == 0);
  assert(ft_isalpha('\0') == 0);
  assert(ft_isalpha('\n') == 0);
  assert(ft_isalpha('@') == 0);
  assert(ft_isalpha('[') == 0);
  assert(ft_isalpha('`') == 0);
  assert(ft_isalpha('{') == 0);
  return 0;
}
