#include "malloc.h"
#include <pthread.h>
#include <stdbool.h>
#include <sys/mman.h>

static bool _lgrow(t_chunk_hdr **chunk) {
  if ((*chunk)->prev && (*chunk)->prev->is_free) {
    *chunk = (*chunk)->prev;
    _grow(*chunk);
    return 1;
  }
  return 0;
}

void free(void *ptr) {
  if (!ptr)
    return;

  pthread_mutex_lock(&_mut);
  if (_setup_alloc()) {
    pthread_mutex_unlock(&_mut);
    return;
  }

  t_zone_hdr *zone;
  t_data_type type;
  t_chunk_hdr *chunk = _find_chunk(ptr, &zone, &type);
  if (!chunk || chunk->is_free) {
    pthread_mutex_unlock(&_mut);
    return; ///< No such chunk; nothing to do.
  }

  chunk->is_free = 1;
  // Right-grow
  while (_grow(chunk))
    ;
  // Left-grow
  while (_lgrow(&chunk))
    ;

  // Chunk is alone and now empty
  if (!chunk->prev && !chunk->next) {
    if (!zone->prev)
      _alloc_conf.zones[type] = zone->next;
    else
      zone->prev->next = zone->next;
    if (zone->next)
      zone->next->prev = zone->prev;
    munmap(zone, zone->nmbytes);
  }
  pthread_mutex_unlock(&_mut);
}
