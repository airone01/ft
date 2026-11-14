#include "test.h"
#include <assert.h>

#define RESET_FLAGS()                                                          \
  do {                                                                         \
    g_invalid_base = 0;                                                        \
    g_no_match = 0;                                                            \
  } while (0)

int main(void) {
  RESET_FLAGS();
  assert(ft_atoi_base("123", "0123456789") == 123);
  RESET_FLAGS();
  assert(ft_atoi_base("-456", "0123456789") == -456);
  RESET_FLAGS();
  assert(ft_atoi_base("+42", "0123456789") == 42);
  RESET_FLAGS();
  assert(ft_atoi_base("  \t 99", "0123456789") == 99);
  RESET_FLAGS();
  assert(ft_atoi_base("  -7", "0123456789") == -7);
  RESET_FLAGS();
  assert(ft_atoi_base("++--9", "0123456789") == 9);
  RESET_FLAGS();
  assert(ft_atoi_base("0", "0123456789") == 0);
  RESET_FLAGS();
  assert(ft_atoi_base("ff", "0123456789abcdef") == 255);
  RESET_FLAGS();
  assert(ft_atoi_base("-ff", "0123456789abcdef") == -255);
  RESET_FLAGS();
  assert(ft_atoi_base("10", "01") == 2);
  RESET_FLAGS();
  assert(ft_atoi_base("1111", "01") == 15);
  RESET_FLAGS();
  assert(ft_atoi_base("z", "0z") == 1);

  /* invalid base: too short */
  RESET_FLAGS();
  ft_atoi_base("1", "0");
  assert(g_invalid_base == 1);

  /* invalid base: contains '+' */
  RESET_FLAGS();
  ft_atoi_base("1", "0+1");
  assert(g_invalid_base == 1);

  /* invalid base: contains '-' */
  RESET_FLAGS();
  ft_atoi_base("1", "0-1");
  assert(g_invalid_base == 1);

  /* invalid base: contains space */
  RESET_FLAGS();
  ft_atoi_base("1", "0 1");
  assert(g_invalid_base == 1);

  /* invalid base: duplicate chars */
  RESET_FLAGS();
  ft_atoi_base("1", "001");
  assert(g_invalid_base == 1);

  /* no match: char not in base */
  RESET_FLAGS();
  ft_atoi_base("9", "01234567");
  assert(g_no_match == 1);

  /* no match: char mid-string not in base */
  RESET_FLAGS();
  ft_atoi_base("12x4", "0123456789");
  assert(g_no_match == 1);

  return 0;
}
