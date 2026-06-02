
#include "../tests.h"

int test_large(void) {
  size_t i;
  char s[10000];

  i = 0;
  while (i < sizeof(s)) {
    s[i] = ' ';
    i++;
  }
  return (!(ft_strlen(s) == sizeof(s) + 1));
}
