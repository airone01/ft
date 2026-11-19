#ifndef SRC_MALLOC_H
#define SRC_MALLOC_H

#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>

#define ALIGN16(x) (((x) % 16) == 0 ? (x) : (((x) + 15) & ~15))

#define MIN_PAYLOAD 16

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
#define ft_free free
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
#define ft_malloc malloc
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
#define ft_realloc realloc

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
} t_data_type;
#define NMDATA_TYPES (Large + 1)

/**
 * @brief Header containing information about the memory chunk.
 * Placed before where the chunk pointer points to.
 *
 * @note A pointer to a 't_chunk_hdr' must ALWAYS point to the header, NOT the
 * data space after (this is what 'void*' is for).
 *
 * @see https://stackoverflow.com/a/24933481
 * @see https://stackoverflow.com/a/4306269
 */
typedef struct s_chunk_hdr {
  /// Size of the chunk in bytes, header included
  size_t nmbytes;
  unsigned int is_free : 1;
  struct s_chunk_hdr *prev;
  struct s_chunk_hdr *next;
} t_chunk_hdr;
#define CHUNK_HDR_SIZE (ALIGN16(sizeof(t_chunk_hdr)))

/**
 * @brief Header containing information about the memory zone.
 *
 * @note A pointer to a 't_zone_hdr' must ALWAYS point to the header, NOT the
 * data space after (this is what 'void*' is for).
 *
 * @see https://stackoverflow.com/a/24933481
 * @see https://stackoverflow.com/a/4306269
 */
typedef struct s_zone_hdr {
  struct s_zone_hdr *prev;
  struct s_zone_hdr *next;
  t_chunk_hdr *chunk; ///< \note Might not even be needed because the first
                      ///< chunk header should always follow

  /// Size of the zone in bytes, header included
  size_t nmbytes;
  t_data_type type;
} t_zone_hdr;
#define ZONE_HDR_SIZE (ALIGN16(sizeof(t_zone_hdr)))

/////////////////////////////// SHARED FUNCTIONS ///////////////////////////////

/**
 * Finds in all lists the first chunk whose pointer corresponds to the passed
 * pointer.
 * @param ptr The user-provided pointer
 * @param[out] zone The zone to save when found
 * @param[out] type The data type to save when found
 * @return The found chunk
 * @return NULL on chunk not found
 */
t_chunk_hdr *_find_chunk(void *ptr, t_zone_hdr **zone, t_data_type *type);

/**
 * Splits 'lchunk' at 'lchunk_size'.
 * @param size The total number of bytes of the sequence
 * @param size The size of the first chunk
 * @return The second chunk
 * @return NULL if no space
 */
t_chunk_hdr *_split(t_chunk_hdr *lchunk, size_t full_nmbytes, size_t size);

/**
 * Merges a chunk and its next one if existing and both are free
 * @return Whether it grew
 */
bool _grow(t_chunk_hdr *lchunk);

/**
 * Shrinks 'chunk' to 'total' bytes (header included). The rest becomes a free
 * chunk if it is big enough to be one, and is merged with a free next chunk.
 * @warn This is probably not agnostic and will have side effects, as it was
 * made inline for realloc. Need to check thoroughly.
 */
void _shrink(t_chunk_hdr *lchunk, size_t total);

/**
 * Sets up the global object ft_malloc config if unset.
 */
int _setup_alloc(void);

/////////////////////////// FT_MALLOC DEBUG ENV VARS ///////////////////////////

// Described here are the environment variables for controlling malloc. They
// were greatly inspired by glibc, specifically my PC's version, 2.44.

typedef enum {
  NotFound,
  DoubleFree,
} t_err;

typedef enum {
  /// @see mallopt(3)
  ///
  /// Setting this parameter controls how 'ft_malloc' responds when various
  /// kinds of programming errors are detected (e.g., freeing the same pointer
  /// twice). The 3 least significant bits (2, 1 and 0) of the value assigned to
  /// this parameter determine the 'ft_malloc' behavior, as follows:
  ///
  /// Bit 0: If this bit is set, then print a one-line message on stderr that
  ///        provides details about the error. The message starts with the
  ///        string "*** ft_malloc detected ***", followed by the program name,
  ///        the name of the memory-allocation function in which the error was
  ///        detected, a brief explanation of the error, and the memory address
  ///        where the error was detected.
  /// Bit 1: If this bit is set, then, after printing any error message
  ///        specified by bit 0, the program is terminated by calling abort(3).
  ///        If bit 0 is also set, then between printing the error message and
  ///        aborting, the program also prints the process's memory mapping in
  ///        the style described in the subject.
  /// Bit 2: This bit only has an effect if bit 0 is also set. If this bit is
  ///        set, then the one-line message describing the error is simplified
  ///        to contain just the name of the function where the error was
  ///        detected and the brief description of the error.
  ///
  /// In order, these bits are aliased by M_CA_EMSG, M_CA_ABRT, and M_CA_SMPL.
  /// The remaining bits are ignored.
  ///
  /// Combining the above details, the following numeric values are meaningful
  /// for M_CHECK_ACTION:
  ///
  /// 0: Ignore error conditions; continue execution (with undefined results).
  /// 1: Print a detailed error message and continue execution.
  /// 2: Abort the program.
  /// 3: Print a detailed error message, and abort the program.
  /// 5: Print a simple error message and continue execution.
  /// 7: Print a detailed error message, and abort the program.
  ///
  /// @example
  /// // This makes the app print a message and abort on ft_malloc error.
  /// mallopt(M_CHECK_ACTION, M_CA_EMBS | M_CA_ABRT);
  M_CHECK_ACTION,

  /// @see mallopt(3)
  ///
  /// If this parameter is set to a nonzero value, then bytes of allocated
  /// memory (other than allocations via calloc(3)) are initialized to the
  /// complement of the value in the least significant byte of the value, the
  /// freed bytes are set to the least significant byte of value.
  /// This can be useful for detecting errors where the programs incorrectly
  /// rely on allocated memory being initialized to zero, or reuse values in
  /// memory that has already been freed.
  ///
  /// The default value for this parameter is 0.
  M_PERTURB,
} t_debug_flag;
#define NMDEBUG_FLAGS (M_PERTURB + 1)

enum {
  M_CA_NONE = 0,
  M_CA_EMSG = 1 << 0,
  M_CA_ABRT = 1 << 1,
  M_CA_SMPL = 1 << 2,
};

/**
 * Set memory allocation parameters.
 * @param param The property to set
 * @param value The value of the property
 * @see malloc.h
 * @see mallopt(3)
 */
int mallopt(t_debug_flag param, int value);

void _dbg_env_load(unsigned int cfg[NMDEBUG_FLAGS]);

void _err(t_err error, void *ptr, const char *fname);

/////////////////////////////// GLOBAL CONFIG ///////////////////////////////

typedef enum { OP_MALLOC, OP_FREE, OP_REALLOC } t_op;
typedef struct {
  t_op op;
  void *ptr; ///< Result
  size_t size;
} t_hist_entry;

#ifndef M_HIST_LEN
#define M_HIST_LEN 1000
#endif /* M_HIST_LEN */

/**
 * @brief Global allocation settings and data
 */
typedef struct {
  unsigned int initialized;
  /// Sizes
  size_t page_size;
  /// Sizes in bytes of data size levels.
  /// 'sizes[0]' is tiny
  /// 'sizes[1]' is small
  /// Large is any larger size
  /// \see DataType
  size_t sizes[NMDATA_TYPES - 1];
  /// Pointers to memory zones.
  /// Same as 'sizes'.
  t_zone_hdr *zones[NMDATA_TYPES];
  /// Debug configuration
  unsigned int debug[NMDEBUG_FLAGS];
  /// Allocation history
  t_hist_entry hist[M_HIST_LEN];
  /// Number of elements in hists
  unsigned int nhist;
} t_alloc_conf;

extern t_alloc_conf _alloc_conf;
extern pthread_mutex_t _mut;

#endif /* SRC_MALLOC_H */
