#include "test.h"

int main(void) {
  int pfd[2];
  assert(pipe(pfd) == 0);

  ft_putchar_fd('4', pfd[1]);
  ft_putchar_fd('2', pfd[1]);
  close(pfd[1]);

  char buf[8] = {0};
  ssize_t n = read(pfd[0], buf, sizeof(buf) - 1);
  close(pfd[0]);

  assert(n == 2);
  assert(buf[0] == '4');
  assert(buf[1] == '2');
  assert(buf[2] == '\0');

  return 0;
}
