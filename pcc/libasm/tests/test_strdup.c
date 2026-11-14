#include "test.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  const char *orig1 = "A language that doesn't have everything is actually "
                      "easier to program in than some that do — Dennis Ritchie";
  char *dup1 = ft_strdup(orig1);

  assert(dup1 != orig1);
  assert(strcmp(dup1, orig1) == 0);
  free(dup1);

  const char *orig2 = "";
  char *dup2 = ft_strdup(orig2);

  assert(dup2 != orig2);
  assert(strcmp(dup2, orig2) == 0);
  free(dup2);

  return 0;
}
