#include "test.h"

int main(void) {
  const char *s = "0123456789";

  // Middle substring
  char *sub = ft_substr(s, 2, 4);
  assert(sub != NULL);
  assert(strcmp(sub, "2345") == 0);
  free(sub);

  // Substring from beginning
  sub = ft_substr(s, 0, 3);
  assert(sub != NULL);
  assert(strcmp(sub, "012") == 0);
  free(sub);

  // Len exceeds string length
  sub = ft_substr(s, 7, 20);
  assert(sub != NULL);
  assert(strcmp(sub, "789") == 0);
  free(sub);

  // Start >= strlen(s) -> returns allocated empty string
  sub = ft_substr(s, 15, 5);
  assert(sub != NULL);
  assert(strcmp(sub, "") == 0);
  free(sub);

  // Start == strlen(s) -> returns allocated empty string
  sub = ft_substr(s, 10, 5);
  assert(sub != NULL);
  assert(strcmp(sub, "") == 0);
  free(sub);

  // len == 0 -> returns allocated empty string
  sub = ft_substr(s, 3, 0);
  assert(sub != NULL);
  assert(strcmp(sub, "") == 0);
  free(sub);

  return 0;
}
