#ifndef SRC_MALLOC_H
#define SRC_MALLOC_H

#include <stddef.h>

/**
 * @brief Frees 'ptr' (assuming it was provided by 'malloc()').
 *
 * It does so by looking before the address zone pointed to by 'ptr'. The
 * header there gives the full size of the allocated zone, which 'free' uses
 * to free.
 *
 * @param ptr The pointer to a memory zone allocated by 'malloc()'.
 * @see free(3)
 */
void free(void *ptr);
/**
 * @brief Allocates 'size' bytes of memory and returns a pointer to the
 * allocated memory.
 *
 * @param size The size of the expected memory zone in bytes.
 * @return Pointer to a memory zone of AT LEAST 'size' bytes.
 * @return NULL on failure.
 * @see malloc(3)
 */
void *malloc(size_t size);
/**
 * Changes the size of the allocation pointed to by 'ptr' to 'size', and returns
 * 'ptr'. If there is not enough room to enlarge the memory allocation pointed
 * to by 'ptr', 'realloc()' creates a new allocation and copies as much of the
 * old data pointed to by 'ptr' as will fit to the new allocation. Then it frees
 * the old allocation, and returns a pointer to the allocated memory.
 *
 * @param ptr The pointer to memory zone allocated by 'malloc()'.
 *            If NULL, 'malloc()' will be used instead.
 * @param size The size of the expected memory zone in bytes.
 * @return 'ptr' on success with enough size.
 * @return When 'realloc()' didn't have enough zone, a new pointer to a new
 *         memory zone of AT LEAST 'size' bytes.
 * @return NULL on failure.
 * @see malloc(3)
 */
void *realloc(void *ptr, size_t size);

/**
 * @example Output
 * TINY : 0xA0000
 * 0xA0020 - 0xA004A : 42 bytes
 * 0xA006A - 0xA00BE : 84 bytes
 * SMALL : 0xAD000
 * 0xAD020 - 0xADEAD : 3725 bytes
 * LARGE : 0xB0000
 * 0xB0020 - 0xBBEEF : 48847 bytes
 * Total : 52698 bytes
 */
void show_alloc_mem(void);

typedef enum {
  Tiny = 0,
  Small = 1,
  Large = 2,
} DataType;
#define NmDataSizes Large + 1

/**
 * @brief Header containing information about the memory zone.
 *
 * @see https://stackoverflow.com/a/24933481
 * @see https://stackoverflow.com/a/4306269
 */
typedef struct {
  void *prev;
  void *next;
  void *chunk;       ///< \note Might not even be needed because the first chunk
                     ///< header should always follow
  unsigned int size; ///< Full size of the zone
  DataType type;
} ZoneHdr;

/**
 * @brief Header containing information about the memory chunk.
 * Placed before where the chunk pointer points to.
 *
 * @see https://stackoverflow.com/a/24933481
 * @see https://stackoverflow.com/a/4306269
 */
typedef struct ChnkHdr {
  size_t nmbytes;
  unsigned int is_free : 1;
  struct ChnkHdr *prev;
  struct ChnkHdr *next;
} ChnkHdr;

/**
 * @brief Global allocation settings and data
 */
typedef struct {
  /// Sizes
  size_t page_size;
  /// Sizes in bytes of data size levels.
  /// 'sizes[0]' is tiny
  /// 'sizes[1]' is small
  /// Large is any larger size
  /// \see DataType
  size_t sizes[NmDataSizes - 1];
  /// Pointers to memory zones.
  /// Same as 'sizes'.
  void *zones[NmDataSizes];
} AllocConf;

extern AllocConf alloc_conf;

// Global configuration

/**
 * Calls 'sysconf()' early to save some settings.
 *
 * @note 'sysconf()' results cannot change during a program lifetime.
 * @see sysconf(3)
 */
void setup_alloc(void);

#endif /* SRC_MALLOC_H */
