#include "test.h"

int main(void) {
  // Zero
  char *s = ft_itoa(0);
  assert(s != NULL);
  assert(strcmp(s, "0") == 0);
  free(s);

  // Positive numbers
  s = ft_itoa(7);
  assert(s != NULL);
  assert(strcmp(s, "7") == 0);
  free(s);

  s = ft_itoa(42);
  assert(s != NULL);
  assert(strcmp(s, "42") == 0);
  free(s);

  s = ft_itoa(123456789);
  assert(s != NULL);
  assert(strcmp(s, "123456789") == 0);
  free(s);

  // Negative numbers
  s = ft_itoa(-1);
  assert(s != NULL);
  assert(strcmp(s, "-1") == 0);
  free(s);

  s = ft_itoa(-98765);
  assert(s != NULL);
  assert(strcmp(s, "-98765") == 0);
  free(s);

  // Extremes
  s = ft_itoa(2147483647);
  assert(s != NULL);
  assert(strcmp(s, "2147483647") == 0);
  free(s);

  s = ft_itoa(-2147483648);
  assert(s != NULL);
  assert(strcmp(s, "-2147483648") == 0);
  free(s);

  return 0;
}
