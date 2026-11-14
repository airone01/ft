#include "test.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  int fd = open("/dev/null", O_WRONLY);
  if (fd == -1) {
    printf("could not open() to test valid write\n");
    return 1;
  }

  assert(ft_write(fd, "Testing ft_write...\n", 20) == 20);
  assert(ft_write(fd, "fail", 0) == 0);

  close(fd);

  assert(ft_write(-1, "fail", 4) == -1);
  assert(errno == EBADF);

  return 0;
}
