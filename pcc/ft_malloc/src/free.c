#include "malloc.h"
#include <sys/mman.h>

/// Finds in all lists the first chunk whose pointer to corresponds to the
/// passed pointer.
/// \param ptr The user-provided pointer
/// \param[out] zone The zone to save when found
/// \param[out] type The data type to save when found
/// \return The found chunk
/// \return NULL on chunk not found
static t_chunk_hdr *find_chunk(void *ptr, t_zone_hdr **zone,
                               t_data_type *type) {
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

/// Merges a chunk and its next one if existing and both are free
static void unsplit(t_chunk_hdr *chunk) {
  if (!chunk || !chunk->is_free || !chunk->next || !chunk->next->is_free)
    return;

  chunk->nmbytes += chunk->next->nmbytes;
  chunk->next = chunk->next->next;
  if (chunk->next)
    chunk->next->prev = chunk;
}

void free(void *ptr) {
  if (!ptr)
    return;

  t_zone_hdr *zone;
  t_data_type type;
  t_chunk_hdr *chunk = find_chunk(ptr, &zone, &type);
  if (!chunk || chunk->is_free)
    return; ///< No such chunk; nothing to do.

  chunk->is_free = 1;
  unsplit(chunk);
  if (chunk->prev && chunk->prev->is_free) {
    chunk = chunk->prev;
    unsplit(chunk);
  }

  // Chunk is alone and now empty
  if (!chunk->prev && !chunk->next) {
    if (!zone->prev)
      alloc_conf.zones[type] = zone->next;
    else
      zone->prev->next = zone->next;
    munmap(zone, zone->nmbytes);
  }
}
