#include "test.h"
#include <assert.h>
#include <unistd.h>

int main(void) {
  assert(ft_strlen("hello, world") == 12);
  assert(ft_strlen("") == 0);
  assert(ft_strlen("ft") == 2);
  assert(ft_strlen(NULL) == 0);
  return 0;
}
