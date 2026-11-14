#include "test.h"

int main(void) {
  int pfd[2];
  assert(pipe(pfd) == 0);

  ft_putendl_fd("Line with newline", pfd[1]);
  close(pfd[1]);

  char buf[64] = {0};
  ssize_t n = read(pfd[0], buf, sizeof(buf) - 1);
  close(pfd[0]);

  assert(n == (ssize_t)strlen("Line with newline\n"));
  assert(strcmp(buf, "Line with newline\n") == 0);

  return 0;
}
