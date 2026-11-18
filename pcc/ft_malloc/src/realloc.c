#include "malloc.h"
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/// "Slide" the chunk of the header of the next chunk to the right into a free
/// chunk if possible, or abort.
/// \note This only supports right-sidedness, meaning we are growing 'lchunk',
/// not shrinking it. Use _slide_hdr_l for this.
/// \note This is tailored for 'realloc()', so it only works when
/// 'lchunk->next->is_free' is true.
/// \param chunk The leftmost chunk
/// \param size The expected data size
/// \return Whether 'realloc()' sould "grow in place"
static bool _slide_hdr_r(t_chunk_hdr *lchunk, size_t size) {
  // Note: the check here is needed still even though it's also done in
  // '_split()', because we run '_grow()' before '_split()' and don't want to
  // grow for nothing.

  if (lchunk->next && lchunk->next->is_free &&
      (lchunk->nmbytes + lchunk->next->nmbytes >= size + CHUNK_HDR_SIZE)) {
    _grow(lchunk);
    _split(lchunk, lchunk->nmbytes, size);

    return true;
  }

  return false;
}

void *realloc(void *ptr, size_t size) {
  if (!ptr)
    return malloc(size);
  if (size <= 0) {
    errno = EINVAL;
    return NULL;
  }
  pthread_mutex_lock(&_mut);
  if (_setup_alloc()) {
    pthread_mutex_unlock(&_mut);
    return NULL;
  }

  if (size > SIZE_MAX - ZONE_HDR_SIZE - CHUNK_HDR_SIZE - alloc_conf.page_size) {
    /* Need to catch this since ALIGN16 on SIZE_MAX overflows, looping back*/
    /*to 0. After setup_alloc because we need to know page size. */
    errno = ENOMEM;
    pthread_mutex_unlock(&_mut);
    return NULL;
  }

  t_zone_hdr *zone;
  t_data_type type;
  t_chunk_hdr *chunk = _find_chunk(ptr, &zone, &type);
  if (!chunk) {
    // Abort with NULL if a bad pointer was passed.
    // May or may not be the expected behavior.
    // TODO: check this
    errno = EINVAL;
    pthread_mutex_unlock(&_mut);
    return NULL;
  }

  size = ALIGN16(size);
  size_t needed = CHUNK_HDR_SIZE + size;
  size_t orig_size = chunk->nmbytes - CHUNK_HDR_SIZE;

  if (chunk->nmbytes >= size + CHUNK_HDR_SIZE) {
    // Too big, need to shrink
    _shrink(chunk, needed);
    pthread_mutex_unlock(&_mut);
    return ptr;
  }

  if (_slide_hdr_r(chunk, size)) {
    // Enough space to "grow in place"
    pthread_mutex_unlock(&_mut);
    return ptr;
  }

  pthread_mutex_unlock(&_mut);
  void *nwptr = malloc(size);
  if (!nwptr)
    return NULL;
  memcpy(nwptr, ptr, orig_size);
  free(ptr);
  return nwptr;
}
