#include "malloc.h"
#include <assert.h>
#include <unistd.h>

int main(void) {
  size_t size = 4 * sizeof(char);
  char *p = malloc(size);

  t_zone_hdr *zone = (t_zone_hdr *)((char *)p - CHUNK_HDR_SIZE - ZONE_HDR_SIZE);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Warray-bounds"
  assert(zone->prev == NULL);
  assert(zone->next == NULL);
  assert(zone->type == Tiny);
  assert(zone->chunk != NULL);
  assert(zone->nmbytes > alloc_conf.page_size);
#pragma GCC diagnostic pop
}
