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
 * @brief Duplicates a NUL-terminated string
 * @returns pointer to duplicated string on success, NULL otherwise
 */
char *strdup(const char *s);

/**
 * @brief Reads symbolic link target using POSIX readlink
 * @returns pointer to target string on success, NULL otherwise
 */
char *read_symlink_target(const char *path, off_t st_size);

/**
 * @brief Checks for extended attributes (@) or ACL (+) on a file path
 */
char get_xattr_acl_char(const char *path);

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
 * @brief Frees dynamic allocations for an array of TempFile structs and the
 * array itself
 */
void free_temp_files(TempFile *files, size_t count);

/**
 * @brief Joins directory path and file name into a relative path string
 */
char *path_join(const char *dir, const char *file);

/**
 * @brief Gets xattrs, ACL, and symlink infos and appends them to a temp file
 */
void enrich_temp_file(TempFile *tf, const CliOptions *optsp);

#endif /* UTIL_H */
