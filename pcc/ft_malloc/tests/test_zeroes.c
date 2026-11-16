#include "malloc.h"
#include <assert.h>

/// This tests whether we're using mmap(3) correctly. The kernel zeroes the
/// memory spaces given, so this should only work on the first allocation.

int main(void) {
  size_t size = 64 * sizeof(char);
  char *p = malloc(size);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Warray-bounds"
  for (int i = 0; i < 64; i++) {
    assert(p[i] == 0);
  }
  assert(p[64] != 0);
#pragma GCC diagnostic pop
}
