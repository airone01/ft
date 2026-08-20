#ifndef LS_H
#define LS_H

#include <stddef.h>
#include <sys/stat.h>

typedef struct {
  int longlist;
  int recursive;
  int all;
  int reverse;
  int timesort;
  int color;

  size_t npaths;
  const char **paths;
} CliOptions;

typedef struct File {
  // d_name; for printing
  char *name;
  // Relative or absolute path for stat/open
  char *path;
  // Cached lstat struct
  struct stat stat;
  // Error code if stat/access failed (0 if success)
  int err_code;
  // For symlinks with -l
  char *link_target;
  // Resolved user name (or id on lack thereof)
  char *user;
  // Resolved group name (or id on lack thereof)
  char *group;
  // '@', '+' or ' ' for extended attrs
  char xattr_acl;
  struct File *next;
} File;

typedef struct tFile {
  // argv or d_name
  char *name;
  // Full path for stat/open
  char *path;
  // Cached lstat struct
  struct stat stat;
  // Error code if stat failed
  int err_code;
  // For symlinks with -l
  char *link_target;
  int uid;
  int gid;
  // '@', '+' or ' ' for extended attrs
  char xattr_acl;
  struct tFile *next;
} tFile;

typedef struct {
  File *err_files;
  size_t nerr;

  File *files;
  size_t nfiles;

  File *dirs;
  size_t ndirs;
} FileLists;

typedef struct {
  int links;
  int user;
  int group;
  int size;
  int major;
  int minor;
} ColWidth;

/**
 * CLI arguments parser
 * @returns 0 on success
 * @returns -1 on error
 * @returns -2 on success but quit immediately
 */
int argsp(int argc, const char *argv[], CliOptions *opts);

/**
 * @brief Options interpreter
 * Categorizes command line path arguments into three lists:
 *   1. flists->err_files: files with stat/access errors
 *   2. flists->files: non-directory files
 *   3. flists->dirs: directories
 * @returns 0 on success
 * @returns -1 on memory or system error
 */
int argsi(CliOptions *opts, FileLists *flists);

/**
 * char *strndup(size_t n;
 *               const char s[n], size_t n);
 *
 * @brief Duplicates a string
 * @returns NULL on error
 * @returns pointer to duplicated string on success
 */
char *strndup(const char *s, size_t n);
/**
 * @brief Duplicates a string
 * @returns NULL on error
 * @returns pointer to duplicated string on success
 */
char *strdup(const char *s);

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

#endif /* LS_H */
