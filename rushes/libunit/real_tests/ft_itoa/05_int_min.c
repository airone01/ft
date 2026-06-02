
#include "../tests.h"

int itoa_int_min_test(void) {
  char *str;
  int res;

  str = ft_itoa(-2147483648);
  res = ft_strncmp(str, "-2147483648", 15);
  free(str);
  return (res);
}
