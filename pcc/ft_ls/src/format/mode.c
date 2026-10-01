#include "metadata.h"

// https://man7.org/linux/man-pages/man0/sys_stat.h.0p.html
void mode_str(mode_t mode, char xattr_acl, int any_xattr_acl, char str[12]) {
  if (S_ISREG(mode))
    str[0] = FileRegular;
  else if (S_ISDIR(mode))
    str[0] = FileDirectory;
  else if (S_ISLNK(mode))
    str[0] = FileSymlink;
  else if (S_ISCHR(mode))
    str[0] = FileCharSpecial;
  else if (S_ISBLK(mode))
    str[0] = FileBlockSpecial;
  else if (S_ISFIFO(mode))
    str[0] = FileFifo;
  else if (S_ISSOCK(mode))
    str[0] = FileSocket;
  else
    str[0] = FileUnknown;

  // User
  str[1] = (mode & S_IRUSR) ? ModeRead : ModeOff;
  str[2] = (mode & S_IWUSR) ? ModeWrite : ModeOff;
  if (mode & S_ISUID)
    str[3] = (mode & S_IXUSR) ? ModeSetugid : ModeSetugidNonExec;
  else
    str[3] = (mode & S_IXUSR) ? ModeExec : ModeOff;

  // Group
  str[4] = (mode & S_IRGRP) ? ModeRead : ModeOff;
  str[5] = (mode & S_IWGRP) ? ModeWrite : ModeOff;
  if (mode & S_ISGID)
    str[6] = (mode & S_IXGRP) ? ModeSetugid : ModeSetugidNonExec;
  else
    str[6] = (mode & S_IXGRP) ? ModeExec : ModeOff;

  // Other
  str[7] = (mode & S_IROTH) ? ModeRead : ModeOff;
  str[8] = (mode & S_IWOTH) ? ModeWrite : ModeOff;
  if (mode & S_ISVTX)
    str[9] = (mode & S_IXOTH) ? ModeSticky : ModeStickyNonExec;
  else
    str[9] = (mode & S_IXOTH) ? ModeExec : ModeOff;

  if (any_xattr_acl) {
    str[10] = (xattr_acl == '@' || xattr_acl == '+') ? xattr_acl : ' ';
    str[11] = '\0';
  } else {
    str[10] = '\0';
  }
}
