#include "test.h"

int main(void) {
  assert(ft_tolower('A') == 'a');
  assert(ft_tolower('Z') == 'z');
  assert(ft_tolower('M') == 'm');
  assert(ft_tolower('a') == 'a');
  assert(ft_tolower('z') == 'z');
  assert(ft_tolower('9') == '9');
  assert(ft_tolower('?') == '?');
  assert(ft_tolower('\0') == '\0');
  return 0;
}
