#include "test.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *s = calloc(128, sizeof(const char));
  const char *o =
      "Violence is the last refuge of the incompetent — Isaac Asimov";
  const char *sn = ft_strcpy(s, o);
  char dest_buf[10] = "overwrite";

  assert(strcmp(sn, o) == 0);
  assert(sn == s);
  ft_strcpy(dest_buf, "");
  assert(dest_buf[0] == '\0');
  assert(dest_buf[1] == 'v');

  free(s);
  return 0;
}
