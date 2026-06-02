
#include "../tests.h"
#include <stdlib.h>

int strdup_basic_test(void) {
  char *str;
  int res;

  str = ft_strdup("Hello, World !");
  res = ft_strncmp(str, "Hello, World !", 14);
  free(str);
  return (res);
}
