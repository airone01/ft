#include "test.h"

static char shift_by_index(size_t i, char c) { return (char)(c + i); }

int main(void) {
  // "0000" with f(i, c) -> '0'+0, '0'+1, '0'+2, '0'+3 -> "0123"
  char *res = ft_strmapi("0000", shift_by_index);
  assert(res != NULL);
  assert(strcmp(res, "0123") == 0);
  free(res);

  // Empty string
  res = ft_strmapi("", shift_by_index);
  assert(res != NULL);
  assert(strcmp(res, "") == 0);
  free(res);

  return 0;
}
