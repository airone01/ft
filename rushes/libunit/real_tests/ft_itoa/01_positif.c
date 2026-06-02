
#include "../tests.h"

int itoa_positif_test(void) {
  char *str;
  int res;

  str = ft_itoa(42);
  res = ft_strncmp(str, "42", 10);
  free(str);
  return (res);
}
