
#include <signal.h>

int test_sigabrt(void) {
  raise(SIGABRT);
  return (1);
}
