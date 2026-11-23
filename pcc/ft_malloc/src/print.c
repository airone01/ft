#include "malloc.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/// \param[in/out] total_nmbytes
void display_large_zone(t_zone_hdr *zone, size_t *total_nmbytes) {
  if (!zone || !zone->chunk)
    return;

  if (zone->next && zone->next->chunk && (zone->chunk >= zone->next->chunk))
    display_large_zone(zone->next, total_nmbytes);

  if (!zone->chunk->is_free) {
    *total_nmbytes += zone->chunk->nmbytes - CHUNK_HDR_SIZE;
    printf("LARGE : 0x%" PRIXPTR "\n", (unsigned long)zone);
    printf("0x%" PRIXPTR " - 0x%" PRIXPTR " : %zu bytes\n",
           (unsigned long)((char *)zone->chunk + CHUNK_HDR_SIZE),
           (unsigned long)((char *)zone->chunk + zone->chunk->nmbytes),
           zone->chunk->nmbytes - CHUNK_HDR_SIZE);
  }

  if (zone->next && zone->next->chunk && (zone->chunk < zone->next->chunk))
    display_large_zone(zone->next, total_nmbytes);
}

/// \param[in/out] total_nmbytes
void display_chunk(t_chunk_hdr *chunk, size_t *total_nmbytes) {
  if (!chunk)
    return;

  if (chunk->next && (chunk >= chunk->next))
    display_chunk(chunk->next, total_nmbytes);

  if (!chunk->is_free) {
    *total_nmbytes += chunk->nmbytes - CHUNK_HDR_SIZE;
    printf("0x%" PRIXPTR " - 0x%" PRIXPTR " : %zu bytes\n",
           (unsigned long)((char *)chunk + CHUNK_HDR_SIZE),
           (unsigned long)((char *)chunk + chunk->nmbytes),
           chunk->nmbytes - CHUNK_HDR_SIZE);
  }

  if (chunk->next && (chunk < chunk->next))
    display_chunk(chunk->next, total_nmbytes);
}

void show_alloc_mem(void) {
  char *tnames[NMDATA_TYPES - 1] = {"TINY", "SMALL"};

  size_t total_nmbytes = 0;

  for (t_data_type type = 0; type < NMDATA_TYPES - 1; type++) {
    for (t_zone_hdr *zone = _alloc_conf.zones[type]; zone; zone = zone->next) {
      printf("%s : 0x%" PRIXPTR "\n", tnames[type], (unsigned long)zone);
      display_chunk(zone->chunk, &total_nmbytes);
    }
  }
  display_large_zone(_alloc_conf.zones[Large], &total_nmbytes);

  printf("Total : %zu bytes\n", total_nmbytes);
}

void show_alloc_mem_ex(void) {
  const char *names[3] = {"free()   ", "malloc() ", "realloc()"};

  fprintf(stderr, "*** ft_malloc usage history ***\n");
  for (unsigned int i = 0; i < _alloc_conf.nhist; i++) {
    t_hist_entry ent = _alloc_conf.hist[i];
    fprintf(stderr, "%s : 0x%" PRIXPTR " : %zu bytes\n", names[ent.op],
            (unsigned long)ent.ptr, ent.size);
  }
}

static void _dump_zone(t_zone_hdr *zone) {
  for (; zone; zone = zone->next) {
    for (t_chunk_hdr *chunk = zone->chunk; chunk; chunk = chunk->next) {
      if (chunk->is_free)
        continue;
      const unsigned char *ptr = (const unsigned char *)chunk + CHUNK_HDR_SIZE;
      size_t size = chunk->nmbytes - CHUNK_HDR_SIZE;
      fprintf(stderr, "0x%" PRIXPTR " : %zu bytes\n", (unsigned long)ptr, size);

      // One line is 16 bytes, so 32 hex chars in packs of 4
      for (size_t i = 0; i < size + 16; i += 16) {
        fprintf(stderr, "%08zx", i);
        if (i < size)
          fprintf(stderr, " ");
        for (size_t j = 0; j < 16; j++) {
          if (i + j < size) {
            fprintf(stderr, "%02x", ptr[i * 16 + j]);
            if (j % 2 == 1 && j != 15)
              fprintf(stderr, " ");
          }
        }
        fprintf(stderr, "\n");
      }
    }
  }
}

void show_alloc_mem_dump(void) {
  fprintf(stderr, "*** ft_malloc stack dump ***\n");
  for (t_data_type type = 0; type < NMDATA_TYPES - 1; type++)
    for (t_zone_hdr *zone = _alloc_conf.zones[type]; zone; zone = zone->next)
      _dump_zone(zone);
  _dump_zone(_alloc_conf.zones[Large]);
}
