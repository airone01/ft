#include "malloc.h"
#include <inttypes.h>
#include <stdio.h>
#include <sys/types.h>

void show_alloc_mem(void) {
  char *tnames[3] = {"TINY", "SMALL", "LARGE"};

  size_t total_nmbytes = 0;

  for (t_data_type type = 0; type < NMDATA_TYPES; type++) {
    t_zone_hdr *zone = alloc_conf.zones[type];

    for (; zone; zone = zone->next) {
      printf("%s : 0x%" PRIXPTR "\n", tnames[type], zone);
      for (t_chunk_hdr *chunk = zone->chunk; chunk; chunk = chunk->next) {
        if (!chunk->is_free) {
          printf(
              "0x%" PRIXPTR " - 0x%" PRIXPTR " : %zu bytes\n",
              (t_chunk_hdr *)((char *)chunk + CHUNK_HDR_SIZE),
              (t_chunk_hdr *)((char *)chunk + chunk->nmbytes + CHUNK_HDR_SIZE),
              chunk->nmbytes);
          total_nmbytes += chunk->nmbytes;
        }
      }
    }
  }
  printf("Total : %zu bytes\n", total_nmbytes);
}
