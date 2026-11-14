#include "test.h"

int main(void) {
  int pfd[2];
  assert(pipe(pfd) == 0);

  char msg[] = "Hello, 42 Network!";
  ft_putstr_fd(msg, pfd[1]);
  close(pfd[1]);

  char buf[64] = {0};
  ssize_t n = read(pfd[0], buf, sizeof(buf) - 1);
  close(pfd[0]);

  assert(n == (ssize_t)strlen(msg));
  assert(strcmp(buf, msg) == 0);

  return 0;
}
