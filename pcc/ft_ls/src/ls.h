#ifndef LS_H
#define LS_H

#include <sys/stat.h>

typedef struct {
  // argv or d_name
  char *name;
  // Full path for stat/open
  char *path;
  // Cached lstat struct
  struct stat stat;
  // For symlinks with -l
  char *link_target;
  char *user;
  char *group;
  // '@', '+' or ' ' for extended attrs
  char xattr_acl;
  struct s_file *next;
} File;

typedef struct {
  int l;
  int R;
  int a;
  int r;
  int t;
  int color;
} CliOptions;

typedef struct {
  int links;
  int user;
  int group;
  int size;
  int major;
  int minor;
} ColWidth;

int parseopts(int argc, char *argv[], CliOptions *opts);

#endif /* LS_H */
