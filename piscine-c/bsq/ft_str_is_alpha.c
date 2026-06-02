
#include "h_main.h"

bool char_is_alpha(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool char_is_num(char c) { return (c >= '0' && c <= '9'); }
