#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern unsigned long ft_strlen(const char *s);
extern const char *ft_strcpy(const char *dst, const char *src);

int main(void) {
  {
    printf("len = %lu\n", ft_strlen("hello, world")); // 12
    printf("len = %lu\n", ft_strlen(""));             // 0
  }

  {
    char *s = calloc(128, sizeof(const char));
    const char *sn = ft_strcpy(
        s, "Violence is the last refuge of the incompetent. - Isaac Asimov");
    printf("copied string: \"%s\"\n", s);
    printf("is the return value the original dest ptr (should be): %d\n",
           sn == s);
    free(s);
  }

  return 0;
}
