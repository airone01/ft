#include "malloc.h"
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t _mut;
t_alloc_conf _alloc_conf = {
    .initialized = 0,
    .page_size = -1,
    .sizes = {-1, -1},
    .zones = {NULL, NULL, NULL},
    .debug = {M_CA_NONE, 5},
};

int _setup_alloc(void) {
  if (!_alloc_conf.initialized) {
    int pr = 0;
    if ((pr = pthread_mutex_init(&_mut, NULL))) {
      errno = pr;
      return pr;
    }

    _alloc_conf.initialized = 1;
    _dbg_env_load(_alloc_conf.debug);
    /* These sizes on my machine are in order: 4096, 128, and 1024. */
    _alloc_conf.page_size = sysconf(_SC_PAGESIZE);
    _alloc_conf.sizes[Tiny] = _alloc_conf.page_size / 32;
    _alloc_conf.sizes[Small] = _alloc_conf.page_size / 4;
  }
  return 0;
}

bool _grow(t_chunk_hdr *lchunk) {
  if (!lchunk || !lchunk->next || !lchunk->next->is_free)
    return false;

  lchunk->nmbytes += lchunk->next->nmbytes;
  lchunk->next = lchunk->next->next;
  if (lchunk->next)
    lchunk->next->prev = lchunk;
  return true;
}

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
    t_zone_hdr *lzone = _alloc_conf.zones[ltype];
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

void _rec_hist(t_hist_entry hist) {
  if (_alloc_conf.nhist >= M_HIST_LEN) {
    memset(_alloc_conf.hist, '\0', M_HIST_LEN * sizeof(t_hist_entry));
    _alloc_conf.nhist = 0;
  }

  _alloc_conf.hist[_alloc_conf.nhist++] = hist;
}
