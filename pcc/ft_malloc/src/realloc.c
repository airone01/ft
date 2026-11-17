#include "malloc.h"
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void *realloc(void *ptr, size_t size) {
  if (!ptr)
    return malloc(size);

  SETUP_ALLOC

  t_zone_hdr *zone;
  t_data_type type;
  t_chunk_hdr *chunk = _find_chunk(ptr, &zone, &type);
  if (!chunk) {
    // Abort with NULL if a bad pointer was passed.
    // May or may not be the expected behavior.
    // TODO: check this
    errno = EINVAL;
    return NULL;
  }
  size_t orig_size = chunk->nmbytes - CHUNK_HDR_SIZE;

  if (chunk->nmbytes >= size + CHUNK_HDR_SIZE)
    // Already have enough space in chunk
    return ptr;

  /// Total bytes needed for all the data (assuming it were all in a single
  /// chunk).
  size_t needed_nmbytes = size + CHUNK_HDR_SIZE;

  // Enough space with next free chunk merged: merge next chunk
  if (chunk->next && chunk->next->is_free &&
      chunk->nmbytes - CHUNK_HDR_SIZE + chunk->next->nmbytes - CHUNK_HDR_SIZE >=
          needed_nmbytes) {
    chunk->next = chunk->next->next;
    chunk->next->prev = chunk;
    chunk->nmbytes = needed_nmbytes;
    return ptr;
  }

  t_chunk_hdr *nwchunk = malloc(size);
  if (!nwchunk)
    return NULL;
  void *nwptr = (void *)((char *)nwchunk - CHUNK_HDR_SIZE);
  memcpy(nwptr, ptr, orig_size);
  return nwptr;
}
