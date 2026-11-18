#include "malloc.h"
#include <unistd.h>

void _setup_alloc(void) {
  if (!alloc_conf.initialized) {
    alloc_conf.initialized = 1;
    /* These sizes on my machine are in order: 4096, 128, and 1024. */
    alloc_conf.page_size = sysconf(_SC_PAGESIZE);
    alloc_conf.sizes[Tiny] = alloc_conf.page_size / 32;
    alloc_conf.sizes[Small] = alloc_conf.page_size / 4;
  }
}

/// Merges a chunk and its next one if existing and both are free
/// \return Whether it grew
bool _grow(t_chunk_hdr *lchunk) {
  if (!lchunk || !lchunk->next || !lchunk->next->is_free)
    return false;

  lchunk->nmbytes += lchunk->next->nmbytes;
  lchunk->next = lchunk->next->next;
  if (lchunk->next)
    lchunk->next->prev = lchunk;
  return true;
}

/// Shrinks 'chunk' to 'total' bytes (header included). The rest becomes a free
/// chunk if it is big enough to be one, and is merged with a free next chunk.
/// \warn This is probably not agnostic and will have side effects, as it was
/// made inline for realloc. Need to check thoroughly.
void _shrink(t_chunk_hdr *chunk, size_t total) {
  size_t rest = chunk->nmbytes - total;
  if (rest < CHUNK_HDR_SIZE + MIN_PAYLOAD)
    return;

  t_chunk_hdr *tail = (t_chunk_hdr *)((char *)chunk + total);
  tail->nmbytes = rest;
  tail->is_free = 1;
  tail->prev = chunk;
  tail->next = chunk->next;
  if (tail->next)
    tail->next->prev = tail;
  chunk->next = tail;
  chunk->nmbytes = total;

  if (tail->next && tail->next->is_free)
    _grow(tail);
}

/// Splits 'lchunk' at 'lchunk_size'.
/// \param size The total number of bytes of the sequence
/// \param size The size of the first chunk
/// \return The second chunk
/// \return NULL if no space
t_chunk_hdr *_split(t_chunk_hdr *lchunk, size_t full_nmbytes,
                    size_t lchunk_size) {
  size_t min_needed_bytes =
      (CHUNK_HDR_SIZE + lchunk_size)   ///< Size of this payload
      + (CHUNK_HDR_SIZE + MIN_PAYLOAD) ///< Size of another potential payload
      ;
  if (full_nmbytes >= min_needed_bytes) {
    t_chunk_hdr *next = lchunk->next;
    lchunk->nmbytes = CHUNK_HDR_SIZE + lchunk_size;

    size_t rshift_size = CHUNK_HDR_SIZE + lchunk_size;
    /// Add the new free chunk
    t_chunk_hdr *rchunk = (t_chunk_hdr *)((char *)lchunk + rshift_size);
    lchunk->next = rchunk;
    lchunk->is_free = 0;

    rchunk->is_free = 1;
    rchunk->next = next;
    rchunk->prev = lchunk;
    rchunk->nmbytes = full_nmbytes - rshift_size;

    if (next != NULL)
      next->prev = rchunk;

    return rchunk;
  } else
    return NULL;
}

t_chunk_hdr *_find_chunk(void *ptr, t_zone_hdr **zone, t_data_type *type) {
  for (t_data_type ltype = 0; ltype < NMDATA_TYPES; ltype++) {
    t_zone_hdr *lzone = alloc_conf.zones[ltype];
    for (; lzone; lzone = lzone->next) {
      t_chunk_hdr *chunk = lzone->chunk;
      for (; chunk; chunk = chunk->next)
        if ((void *)((char *)(chunk) + CHUNK_HDR_SIZE) == ptr) {
          *zone = lzone;
          *type = ltype;
          return chunk;
        }
    }
  }

  return NULL;
}
