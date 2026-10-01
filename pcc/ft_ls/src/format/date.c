#include "metadata.h"

void date_str(time_t _time, char str[32]) {
  struct tm *tm_info = localtime(&_time);
  time_t now = time(NULL);

  if (_time > now || (now - _time) > THRESHOLD_OLD) {
    // older file format
    strftime(str, 32, "%b %e  %Y", tm_info);
  } else {
    // recent file format
    strftime(str, 32, "%b %e %H:%M", tm_info);
  }
}
