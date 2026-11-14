#include "test.h"

int main(void) {
  const char *str = "bonjour bonsoir";

  assert(ft_strrchr(str, 'b') == str + 8);
  assert(ft_strrchr(str, 'o') == str + 12);
  assert(ft_strrchr(str, 'r') == str + 14);
  assert(ft_strrchr(str, 'x') == NULL);
  assert(ft_strrchr(str, '\0') == str + 15);

  assert(ft_strrchr("", 'a') == NULL);
  assert(ft_strrchr("", '\0') != NULL);
  assert(*ft_strrchr("", '\0') == '\0');

  return 0;
}
