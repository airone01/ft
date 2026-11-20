#include "malloc.h"
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

/// Aligns 'num' to a greater multiple of 'mult'.
/// \see https://stackoverflow.com/a/40518597
static size_t align(size_t num, size_t mult) {
  return (num + mult - 1) / mult * mult;
}

static t_data_type resolve_data_size(size_t size) {
  if (size <= _alloc_conf.sizes[Tiny])
    return Tiny;
  if (size <= _alloc_conf.sizes[Small])
    return Small;
  return Large;
}

/// Allocates a zone and writes initial headers.
/// \param data_type The data size to account for.
static void *alloc_zone(t_data_type data_type, size_t total_nmbytes) {
  /// Requests pages from the kernel.
  void *zone_ptr =
      mmap(NULL,          ///< Kernel picks address
           total_nmbytes, ///< Padded on page size
           PROT_READ | PROT_WRITE,
           MAP_ANONYMOUS | MAP_PRIVATE, ///< \todo use MAP_ANON on BSD
           -1,                          ///< No FD
           0                            ///< No offset
      );

  /// 'mmap()' returns MAP_FAILED on failure, not NULL.
  /// Also it sets 'errno'.
  if (zone_ptr == MAP_FAILED)
    return NULL;

  // Now we're safe and we can write initial header followed by chunk header

  t_zone_hdr *zone = (t_zone_hdr *)zone_ptr;
  t_chunk_hdr *first_chnk = (t_chunk_hdr *)((char *)zone_ptr + ZONE_HDR_SIZE);

  zone->type = data_type;
  zone->nmbytes = total_nmbytes;
  zone->chunk = first_chnk;
  zone->next = NULL;
  zone->prev = NULL;

  /// Calculate usable payload capacity for this individual big chunk
  size_t usable_space = total_nmbytes - ZONE_HDR_SIZE;

  first_chnk->nmbytes = usable_space;
  first_chnk->is_free = 1;
  first_chnk->prev = NULL;
  first_chnk->next = NULL;

  return zone_ptr;
}

/// Finds the first chunk in a zone that has enough space.
/// \note No defragmentation
/// \return pointer to free zone
/// \return NULL on null pointer
/// \return NULL on not enough space in zone
static t_chunk_hdr *find_free_chunk_in_zone(t_zone_hdr *zone_ptr,
                                            size_t nmbytes) {
  if (!zone_ptr)
    return NULL;

  t_chunk_hdr *chunk = zone_ptr->chunk;

  while (chunk) {
    if (chunk->is_free && (chunk->nmbytes >= nmbytes))
      return chunk;
    chunk = chunk->next;
  }

  return NULL;
}

/// Allocates a chunk of a set size in a zone.
/// \param zone The zone that has enough space for the chunk.
/// \param size The size of the free space expected by the user.
/// \return NULL on null pointer
/// \return NULL on not enough space in zone
/// \return A pointer to the address of the allocated chunk
static t_chunk_hdr *alloc_chunk(t_zone_hdr *zone_ptr, size_t size) {
  if (!zone_ptr)
    return NULL;

  /// The chunk we will allocate, also the old free chunk.
  t_chunk_hdr *target =
      find_free_chunk_in_zone(zone_ptr, CHUNK_HDR_SIZE + size);
  if (!target)
    return NULL;

  size_t full_nmbytes = target->nmbytes;
  target->is_free = 0;

  _split(target, full_nmbytes, size);

  if (_alloc_conf.debug[M_PERTURB])
    memset((char *)target + CHUNK_HDR_SIZE + 1,
           -(unsigned char)(_alloc_conf.debug[M_PERTURB]), size - 1);

  return target;
}

/// Instead of calculating the size of the zone, I just iterate over the zones
/// until I find one where there is space to allocate a chunk.
static t_chunk_hdr *try_alloc_chunk(t_zone_hdr *zone, size_t size) {
  if (!zone)
    return NULL;

  while (zone) {
    t_chunk_hdr *chunk = alloc_chunk(zone, size);
    if (chunk)
      return chunk;
    zone = zone->next;
  }

  return NULL;
}

static size_t calc_total_nmbytes(t_data_type data_type, size_t size) {
  return data_type == Large
             ? align(ZONE_HDR_SIZE + CHUNK_HDR_SIZE + size,
                     _alloc_conf.page_size)
             : align(ZONE_HDR_SIZE + (100 * (CHUNK_HDR_SIZE +
                                             _alloc_conf.sizes[data_type])),
                     _alloc_conf.page_size);
}

void *malloc(size_t size) {
  if (size <= 0) {
    errno = EINVAL;
    return NULL;
  }

  pthread_mutex_lock(&_mut);
  if (_setup_alloc()) {
    pthread_mutex_unlock(&_mut);
    return NULL;
  }

  if (size >
      SIZE_MAX - ZONE_HDR_SIZE - CHUNK_HDR_SIZE - _alloc_conf.page_size) {
    /* Need to catch this since ALIGN16 on SIZE_MAX overflows, looping back*/
    /*to 0. After setup_alloc because we need to know page size. */
    errno = ENOMEM;
    pthread_mutex_unlock(&_mut);
    return NULL;
  }

  size = ALIGN16(size);
  t_data_type data_type = resolve_data_size(size);

  t_zone_hdr **zone_lst = &_alloc_conf.zones[data_type];
  if (!*zone_lst) {
    size_t total_nmbytes = calc_total_nmbytes(data_type, size);
    t_zone_hdr *z = alloc_zone(data_type, total_nmbytes);
    if (!z) {
      return NULL;
      pthread_mutex_unlock(&_mut);
    }
    *zone_lst = z;
  }

  // Now we have a guaranteed zone for size.
  // We can split to get our chunk
  // Might need to be protected
  // Pointer is decided here, and we can return it

  t_chunk_hdr *chunk = NULL;
  chunk = try_alloc_chunk(*zone_lst, size);
  if (!chunk) {
    // No space in present zones, need to make new zone
    size_t total_nmbytes = calc_total_nmbytes(data_type, size);
    t_zone_hdr *new = alloc_zone(data_type, total_nmbytes);
    if (!new) {
      errno = ENOMEM;
      pthread_mutex_unlock(&_mut);
      return NULL;
    }
    t_zone_hdr *last = *zone_lst;
    while (last->next)
      last = last->next;
    last->next = new;
    new->prev = last;
    chunk = alloc_chunk(new, size);
  }

  if (!chunk) {
    pthread_mutex_unlock(&_mut);
    return NULL;
  }

  void *ret = (void *)((char *)chunk + CHUNK_HDR_SIZE);
  _rec_hist((t_hist_entry){.op = OP_MALLOC, .ptr = ret, .size = size});

  pthread_mutex_unlock(&_mut);

  return ret;
}
