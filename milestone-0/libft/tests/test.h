#ifndef LIBFT_TEST_H
#define LIBFT_TEST_H

#include "libft.h"
#include <assert.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Pipe helper to capture writes to a given fd (e.g. STDOUT_FILENO or custom fd)
static inline void capture_fd_begin(int *pipefd, int *saved_fd, int target_fd) {
  assert(pipe(pipefd) == 0);
  *saved_fd = dup(target_fd);
  dup2(pipefd[1], target_fd);
  close(pipefd[1]);
}

static inline ssize_t capture_fd_end(int pipefd_read, int saved_fd,
                                     int target_fd, char *buf,
                                     size_t buf_size) {
  fflush(NULL);
  dup2(saved_fd, target_fd);
  close(saved_fd);
  ssize_t bytes = read(pipefd_read, buf, buf_size - 1);
  close(pipefd_read);
  if (bytes >= 0)
    buf[bytes] = '\0';
  return bytes;
}

#endif // LIBFT_TEST_H
