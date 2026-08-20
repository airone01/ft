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
  // For symlinks with -l
  char *link_target;
  int uid;
  int gid;
  // '@', '+' or ' ' for extended attrs
  char xattr_acl;
  struct tFile *next;
} tFile;

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
 * @returns 0 on success
 * @returns -1 on error
 * @returns -2 on success but quit immediately
 */
int argsi(CliOptions *opts, File **dfiles);

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

#endif /* LS_H */
