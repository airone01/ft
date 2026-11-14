#include "test.h"

int main(void) {
  // Normal join
  char *res = ft_strjoin("Hello, ", "World!");
  assert(res != NULL);
  assert(strcmp(res, "Hello, World!") == 0);
  free(res);

  // s1 empty
  res = ft_strjoin("", "42");
  assert(res != NULL);
  assert(strcmp(res, "42") == 0);
  free(res);

  // s2 empty
  res = ft_strjoin("Paris", "");
  assert(res != NULL);
  assert(strcmp(res, "Paris") == 0);
  free(res);

  // Both empty
  res = ft_strjoin("", "");
  assert(res != NULL);
  assert(strcmp(res, "") == 0);
  free(res);

  return 0;
}
