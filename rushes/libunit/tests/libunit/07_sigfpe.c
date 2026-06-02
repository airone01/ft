
#include <signal.h>

int test_sigfpe(void) {
  raise(SIGFPE);
  return (1);
}
