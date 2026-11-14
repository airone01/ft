#include "test.h"

static void to_upper_even(unsigned int i, char *c) {
  if (i % 2 == 0 && *c >= 'a' && *c <= 'z') {
    *c = (char)(*c - 32);
  }
}

int main(void) {
  char str[] = "abcdef";
  ft_striteri(str, to_upper_even);
  // Indices 0, 2, 4 modified: 'a'->'A', 'c'->'C', 'e'->'E'
  assert(strcmp(str, "AbCdEf") == 0);

  char empty[] = "";
  ft_striteri(empty, to_upper_even);
  assert(strcmp(empty, "") == 0);

  return 0;
}
