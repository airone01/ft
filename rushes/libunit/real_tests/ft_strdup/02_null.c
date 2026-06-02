
#include "../tests.h"
#include <stdlib.h>

int strdup_null_test(void) {
  char *str;

  str = ft_strdup(NULL);
  if (str)
    free(str);
  return (1);
}
