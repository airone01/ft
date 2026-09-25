#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>
#include <sys/stat.h>

enum DisplayType {
  // (default)
  DisplayPretty = 0,
  // (when piped to a program)
  DisplayPiped = 1,
  // (-l option)
  DisplayLong = 2,
};

typedef struct CliOptions {
  enum DisplayType ltype;
  int recursive;
  int all;
  int reverse;
  int timesort;
  int color;
  int showDate;

  size_t npaths;
  const char **paths;
} CliOptions;

typedef struct File {
  // d_name; for printing
  char *name;
  // Relative or absolute path for stat/open
  char *path;
  // Cached lstat() struct
  struct stat stat;
  // Error code if stat/access failed (0 if success)
  int err_code;
  // For symlinks with -l
  char *link_target;
  // Resolved user name (or ID on lack thereof)
  char *user;
  // Resolved group name (or ID on lack thereof)
  char *group;
  // '@', '+' or ' ' for extended attributes
  char xattr_acl;
  struct File *next;
} File;

typedef struct TempFile {
  // argv or d_name
  char *name;
  // Full path for stat/open
  char *path;
  // Cached lstat() struct
  struct stat stat;
  // Error code if stat failed
  int err_code;
  // For symlinks with -l
  char *link_target;
  int uid;
  int gid;
  // '@', '+' or ' ' for extended attributes
  char xattr_acl;
  struct TempFile *next;
} TempFile;

typedef struct FileLists {
  File *err_files;
  size_t nerr;

  File *files;
  size_t nmemb;

  File *dirs;
  size_t ndirs;
} FileLists;

#endif /* TYPES_H */
