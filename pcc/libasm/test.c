#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern unsigned long ft_strlen(const char *s);
extern const char *ft_strcpy(const char *dst, const char *src);
extern unsigned long ft_strcmp(const char *s1, const char *s2);

void comp_ft_strcmp(const char *s1, const char *s2) {
  printf("'%s' vs '%s' (mine): %zu\n", s1, s2, ft_strcmp(s1, s2));
  printf("'%s' vs '%s' (libc): %d\n", s1, s2, strcmp(s1, s2));
}

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

  {
    const char *s1 = "hello";
    const char *s2 = "hella";
    comp_ft_strcmp(s1, s2);
    s1 = "";
    s2 = "";
    comp_ft_strcmp(s1, s2);
  }

  return 0;
}
