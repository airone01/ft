#include "test.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  char buf[50];
  int fd = open("/dev/urandom", O_RDONLY);
  if (fd == -1) {
    printf("could not open() to test valid read\n");
    return 1;
  }

  size_t ret = ft_read(fd, buf, 10);
  assert(ret == 10);
  assert(ft_read(fd, buf, 0) == 0);
  close(fd);

  ssize_t ret2 = ft_read(-1, buf, 10);
  assert(ret2 == -1);
  assert(errno == EBADF);

  return 0;
}
