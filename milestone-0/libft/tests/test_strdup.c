#include "test.h"

int main(void) {
  const char *orig = "Life, the Universe and Everything";
  char *dup = ft_strdup(orig);

  assert(dup != NULL);
  assert(dup != orig);
  assert(strcmp(dup, orig) == 0);
  assert(strlen(dup) == strlen(orig));
  free(dup);

  // Empty string
  const char *empty = "";
  char *dup_empty = ft_strdup(empty);
  assert(dup_empty != NULL);
  assert(dup_empty != empty);
  assert(strcmp(dup_empty, "") == 0);
  assert(strlen(dup_empty) == 0);
  free(dup_empty);

  return 0;
}
