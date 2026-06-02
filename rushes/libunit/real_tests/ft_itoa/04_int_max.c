
#include "../tests.h"

int itoa_int_max_test(void) {
  char *str;
  int res;

  str = ft_itoa(2147483647);
  res = ft_strncmp(str, "2147483647", 15);
  free(str);
  return (res);
}
