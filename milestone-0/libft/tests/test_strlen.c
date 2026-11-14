#include "test.h"

int main(void) {
  assert(ft_strlen("") == 0);
  assert(ft_strlen("a") == 1);
  assert(ft_strlen("hello") == 5);
  assert(ft_strlen("hello, world!") == 13);
  assert(ft_strlen("42 Network - Paris 19") == 21);

  char long_str[1024];
  memset(long_str, 'x', 1023);
  long_str[1023] = '\0';
  assert(ft_strlen(long_str) == 1023);
  return 0;
}
