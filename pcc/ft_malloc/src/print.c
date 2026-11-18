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
    printf("LARGE : 0x%" PRIXPTR "\n", zone);
    printf("0x%" PRIXPTR " - 0x%" PRIXPTR " : %zu bytes\n",
           (t_chunk_hdr *)((char *)zone->chunk + CHUNK_HDR_SIZE),
           (t_chunk_hdr *)((char *)zone->chunk + zone->chunk->nmbytes),
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
           (t_chunk_hdr *)((char *)chunk + CHUNK_HDR_SIZE),
           (t_chunk_hdr *)((char *)chunk + chunk->nmbytes),
           chunk->nmbytes - CHUNK_HDR_SIZE);
  }

  if (chunk->next && (chunk < chunk->next))
    display_chunk(chunk->next, total_nmbytes);
}

void show_alloc_mem(void) {
  char *tnames[NMDATA_TYPES - 1] = {"TINY", "SMALL"};

  size_t total_nmbytes = 0;

  for (t_data_type type = 0; type < NMDATA_TYPES - 1; type++) {
    t_zone_hdr *zone = alloc_conf.zones[type];

    for (; zone; zone = zone->next) {
      printf("%s : 0x%" PRIXPTR "\n", tnames[type], zone);
      display_chunk(zone->chunk, &total_nmbytes);
    }
  }
  display_large_zone(alloc_conf.zones[Large], &total_nmbytes);

  printf("Total : %zu bytes\n", total_nmbytes);
}
