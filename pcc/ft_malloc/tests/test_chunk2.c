#include "malloc.h"
#include <assert.h>
#include <unistd.h>

int main(void) {
  size_t size = 4 * sizeof(char);
  t_chunk_hdr *old_chunk =
      (t_chunk_hdr *)((char *)malloc(size) - CHUNK_HDR_SIZE);
  t_chunk_hdr *chunk = (t_chunk_hdr *)((char *)malloc(size) - CHUNK_HDR_SIZE);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Warray-bounds"
  assert(chunk->is_free == 0);
  assert(chunk->prev == old_chunk);
  assert(chunk->nmbytes == CHUNK_HDR_SIZE + ALIGN16(size));
#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Warray-bounds"
  t_chunk_hdr *next = chunk->next;
  assert(next != NULL);
  assert(next->is_free == 1);
  assert(next->next == NULL);
  assert(next->prev == chunk);
  assert(next->nmbytes != 0);
#pragma GCC diagnostic pop
}
