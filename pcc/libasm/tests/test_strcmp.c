#include "test.h"
#include <assert.h>
#include <string.h>

void comp_ft_strcmp(const char *s1, const char *s2) {
  int my_res = ft_strcmp(s1, s2);
  int std_res = strcmp(s1, s2);

  int my_sign = (my_res > 0) - (my_res < 0);
  int std_sign = (std_res > 0) - (std_res < 0);

  assert(my_sign == std_sign);
}

int main(void) {
  comp_ft_strcmp("hello", "hella");
  comp_ft_strcmp("hella", "hello");
  comp_ft_strcmp("", "");
  comp_ft_strcmp("\xff", "\x01");
  comp_ft_strcmp("ᓚᘏᗢ", "ᓚᘏᗢ");
  // well it should really not make any difference for 'special' characters or
  // not, but I like the cat :-)
  return 0;
}
