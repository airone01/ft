
#include <signal.h>

int test_sigpipe(void) {
  raise(SIGPIPE);
  return (1);
}
