#include "test.h"

int main(void) {
  // Trim both sides
  char *res = ft_strtrim("   hello world   ", " ");
  assert(res != NULL);
  assert(strcmp(res, "hello world") == 0);
  free(res);

  // Multi-character set
  res = ft_strtrim("xxxyyyhellozzzyyy", "xyz");
  assert(res != NULL);
  assert(strcmp(res, "hello") == 0);
  free(res);

  // Trim only front
  res = ft_strtrim("---test", "-");
  assert(res != NULL);
  assert(strcmp(res, "test") == 0);
  free(res);

  // Trim only back
  res = ft_strtrim("test===", "=");
  assert(res != NULL);
  assert(strcmp(res, "test") == 0);
  free(res);

  // Trim all characters -> returns empty string
  res = ft_strtrim("aaaaaa", "a");
  assert(res != NULL);
  assert(strcmp(res, "") == 0);
  free(res);

  // Empty set -> string unchanged
  res = ft_strtrim("no trim", "");
  assert(res != NULL);
  assert(strcmp(res, "no trim") == 0);
  free(res);

  // Empty string
  res = ft_strtrim("", "abc");
  assert(res != NULL);
  assert(strcmp(res, "") == 0);
  free(res);

  return 0;
}
