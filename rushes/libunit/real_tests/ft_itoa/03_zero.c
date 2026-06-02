
#include "../tests.h"

int itoa_zero_test(void) {
  char *str;
  int res;

  str = ft_itoa(0);
  res = ft_strncmp(str, "0", 10);
  free(str);
  return (res);
}
