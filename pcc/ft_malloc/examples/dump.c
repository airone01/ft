/* This example is about testing 'show_alloc_mem_dump()', which dumps the stack
 * on the standard output.
 * Don't forget to compile with '-fno-builtins'! */

#include "malloc.h"
#include <string.h>

int main(void) {
  char *a = "Hello 42! Here is some text!";
  char *b = malloc(strlen(a) * sizeof(char));
  strcpy(b, a);

  show_alloc_mem_dump();

  free(b);
}
