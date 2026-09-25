#ifndef SRC_FORMAT_METADATA_H
#define SRC_FORMAT_METADATA_H

#include "../types.h"
#include <sys/types.h>
#include <time.h>

#ifndef THRESHOLD_OLD
// Threshold before file is 'old', in seconds.
#define THRESHOLD_OLD 15778463
#endif /* THRESHOLD_OLD */

/**
 * @brief Formats file time
 * @note Writes to a small string buffer `str` for simplicity
 */
void date_str(time_t mtime, char str[32]);

/**
 * @brief Formats file mode bits and xattr/acl indicator into an 11-character
 * permission string
 * @note Writes to a small string buffer `str` for simplicity
 */
void mode_str(mode_t mode, char xattr_acl, int any_xattr_acl, char str[12]);

/**
 * @brief Gets xattrs, ACL, and symlink infos and appends them to a temp file
 */
void enrich_temp_file(TempFile *tf, const CliOptions *optsp);

/**
 * @brief Checks for extended attributes (@) or ACL (+) on a file path
 */
char get_xattr_acl_char(const char *path);

/**
 * @brief Reads symbolic link target using POSIX readlink
 * @returns pointer to target string on success, NULL otherwise
 */
char *read_symlink_target(const char *path, off_t st_size);

#endif /* SRC_FORMAT_METADATA_H */
