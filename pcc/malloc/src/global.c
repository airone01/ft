#include "malloc.h"
#include <assert.h>
#include <unistd.h>

AllocConf alloc_conf = {
    .page_size = -1,
    .sizes = {-1, -1},
    .zones = {NULL, NULL, NULL},
};

void setup_alloc(void) {
  /// Static assert header sizes
  /// \see https://stackoverflow.com/a/19402038
  // TODO: static_assert is C11. Find an equivalent for C99.
  // static_assert(sizeof(ZoneHdr) == 32, "ZoneHdr is not padded");
  // static_assert(sizeof(ChnkHdr) == 32, "ChnkHdr is not padded");

  if (alloc_conf.page_size <= 0) {
    // These sizes on my machine are in order: 4096, 128, and 1024.
    alloc_conf.page_size = sysconf(_SC_PAGESIZE);
    alloc_conf.sizes[Tiny] = alloc_conf.page_size / 32;
    alloc_conf.sizes[Small] = alloc_conf.page_size / 4;
  }
}
