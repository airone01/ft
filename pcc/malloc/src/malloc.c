#include "malloc.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>

#define ALIGN16(x) (((x) + 15) & ~15)

/// Aligns 'num' to a greater multiple of 'mult'.
/// \see https://stackoverflow.com/a/40518597
static size_t align(size_t num, size_t mult) {
  return num + mult - (num % mult);
}

static DataType resolve_data_size(size_t size) {
  if (size <= alloc_conf.sizes[Tiny])
    return Tiny;
  if (size <= alloc_conf.sizes[Small])
    return Small;
  return Large;
}

/// Gets the free space remaining in 'zone' in bytes.
/// \todo
static size_t get_free_space(void *zone) {
  (void)zone;
  return 0;
}

/// Allocates a zone with space for 100 chunks and writes initial headers.
/// \param data_type The data size to account for.
static void *alloc_zone_100(DataType data_type) {
  // Calculate zone size
  size_t total_zone_bytes =
      align(sizeof(ZoneHdr) + (100 * (sizeof(ChnkHdr) + data_type)),
            alloc_conf.page_size);

  /// Requests pages from the kernel.
  void *zone_ptr =
      mmap(NULL,             ///< Kernel picks address
           total_zone_bytes, ///< Padded on page size
           PROT_READ | PROT_WRITE,
           MAP_ANONYMOUS | MAP_PRIVATE, ///< \todo use MAP_ANON on BSD
           -1,                          ///< No FD
           0                            ///< No offset
      );

  /// 'mmap()' returns MAP_FAILED on failure, not NULL.
  /// Also it sets 'errno'.
  if (zone_ptr == MAP_FAILED) {
    perror("mmap failed");
    return NULL;
  }

  // Now we're safe and we can write initial header followed by chunk header

  ZoneHdr *zone = (ZoneHdr *)zone_ptr;
  ChnkHdr *first_chnk =
      (ChnkHdr *)((char *)zone_ptr + ALIGN16(sizeof(ZoneHdr)));

  zone->type = data_type;
  zone->size = total_zone_bytes;
  zone->chunk = first_chnk;
  zone->next = NULL;
  zone->prev = NULL;

  /// Calculate usable payload capacity for this individual big chunk
  size_t hdrs_overhead = ALIGN16(sizeof(ZoneHdr)) + ALIGN16(sizeof(ChnkHdr));
  size_t usable_space = total_zone_bytes - hdrs_overhead;

  first_chnk->nmbytes = usable_space;
  first_chnk->is_free = 1;
  first_chnk->prev = NULL;
  first_chnk->next = NULL;

  return zone_ptr;
}

void *malloc(size_t size) {
  if (size <= 0)
    return NULL;
  size = ALIGN16(size);

  void *zone = NULL;
  (void)zone;

  setup_alloc();

  DataType data_type = resolve_data_size(size);

  if (!alloc_conf.zones[data_type] ||
      (get_free_space(alloc_conf.zones[data_type]) < size))
    // Then we allocate a new zone of required size
    // Also this can fail, protection needed
    zone = alloc_zone_100(data_type);

  // Now we have a guaranteed zone for size.
  // We can split to get our chunk
  // Might need to be protected
  // Pointer is decided here, and we can return it

  return NULL;
}
