
#include <signal.h>

int test_sigkill(void) {
  raise(SIGKILL);
  return (1);
}
