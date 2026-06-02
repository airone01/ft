
#include <stdlib.h>

int test_sigbus(void) {
  char *cptr;
  int *iptr;

  __asm__("pushf\norl $0x40000,(%rsp)\npopf");
  cptr = malloc(sizeof(int) + 1);
  iptr = (int *)++cptr;
  *iptr = 42;
  return (1);
}
