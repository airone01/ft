#include <stdio.h>

extern unsigned long ft_strlen(const char *s);

int main(void) {
  {
    printf("len = %lu\n", ft_strlen("hello, world")); // 12
    printf("len = %lu\n", ft_strlen(""));             // 0
  }

  return 0;
}
