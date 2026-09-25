#include "metadata.h"

void date_str(time_t mtime, char str[32]) {
  struct tm *tm_info = localtime(&mtime);
  time_t now = time(NULL);

  if (mtime > now || (now - mtime) > THRESHOLD_OLD) {
    // older file format
    strftime(str, 32, "%b %e  %Y", tm_info);
  } else {
    // recent file format
    strftime(str, 32, "%b %e %H:%M", tm_info);
  }
}
