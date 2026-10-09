#ifndef TYPES_H
#define TYPES_H

#define PACKET_SIZE 64

#include <stddef.h>
#include <sys/stat.h>

typedef struct CliOptions {
  int verbose;

  const char *address;
  const char *pname;
} CliOptions;

#endif /* TYPES_H */
