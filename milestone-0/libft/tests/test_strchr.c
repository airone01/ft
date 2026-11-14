#include "test.h"

int main(void) {
  const char *str = "hello world";

  assert(ft_strchr(str, 'h') == str);
  assert(ft_strchr(str, 'l') == str + 2);
  assert(ft_strchr(str, 'd') == str + 10);
  assert(ft_strchr(str, 'z') == NULL);
  assert(ft_strchr(str, '\0') == str + 11);

  // Empty string
  assert(ft_strchr("", 'a') == NULL);
  assert(ft_strchr("", '\0') != NULL);
  assert(*ft_strchr("", '\0') == '\0');

  return 0;
}
