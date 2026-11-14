#include "test.h"

int main(void) {
  assert(ft_atoi("0") == 0);
  assert(ft_atoi("42") == 42);
  assert(ft_atoi("+42") == 42);
  assert(ft_atoi("-42") == -42);
  assert(ft_atoi("  \t\n\r\v\f 12345") == 12345);
  assert(ft_atoi("  -987") == -987);
  assert(ft_atoi("42isTheAnswer") == 42);
  assert(ft_atoi("-42abc") == -42);
  assert(ft_atoi("abc42") == 0);
  assert(ft_atoi("+-42") == 0);
  assert(ft_atoi("-+42") == 0);
  assert(ft_atoi("--42") == 0);
  assert(ft_atoi("++42") == 0);
  assert(ft_atoi("") == 0);
  assert(ft_atoi("   ") == 0);

  // Limits
  assert(ft_atoi("2147483647") == 2147483647);
  assert(ft_atoi("-2147483648") == -2147483648);

  return 0;
}
