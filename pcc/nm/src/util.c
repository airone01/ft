#include "util.h"
#include <stdlib.h>
#include <string.h>

char *mstrdup(const char *src) {
  char *dst = malloc((strlen(src) + 1) * sizeof(char));
  if (dst == NULL)
    return NULL;
  strcpy(dst, src);
  return dst;
}
