#ifndef UTIL_H
#define UTIL_H

#include "types.h"
#include <stddef.h>
#include <sys/types.h>

/**
 * char *strndup(size_t n;
 *               const char s[n], size_t n);
 *
 * @brief Duplicates a string
 * @returns pointer to duplicated string on success, NULL otherwise
 */
char *strndup(const char *s, size_t n);

/**
 * @brief Duplicates a NULL-terminated string
 * @returns pointer to duplicated string on success, NULL otherwise
 */
char *strdup(const char *s);

/**
 * @brief Reads symbolic link target using POSIX readlink
 * @returns pointer to target string on success, NULL otherwise
 */
char *read_symlink_target(const char *path, off_t st_size);

/**
 * @brief Formats file time
 * @note Writes to a small string buffer `str` for simplicity
 */
void date_str(time_t mtime, char str[32]);

/**
 * @brief Formats file mode bits into a 10-character permission string
 * @note Writes to a small string buffer `str` for simplicity
 */
void mode_str(mode_t mode, char str[11]);

/**
 * @brief Frees dynamically allocated memory in a single File struct
 */
void free_file(File *file);

/**
 * @brief Frees dynamic allocations for an array of File structs and the array
 * itself
 */
void free_files(File *files, size_t count);

/**
 * @brief Frees all three lists in a FileLists struct
 */
void free_file_lists(FileLists *flists);

/**
 * @brief Joins directory path and file name into a relative path string
 */
char *path_join(const char *dir, const char *file);

#endif /* UTIL_H */
