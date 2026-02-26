#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ASSERT_EQ(actual, expected, label)                                     \
  do {                                                                         \
    if ((actual) == (expected)) {                                              \
      printf("[OK] %s\n", label);                                              \
    } else {                                                                   \
      printf("[KO] %s (line %d): Expected %ld, got %ld\n", label, __LINE__,    \
             (long)(expected), (long)(actual));                                \
    }                                                                          \
  } while (0)

extern unsigned long ft_strlen(const char *s);
extern const char *ft_strcpy(const char *dst, const char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buf, size_t count);

void comp_ft_strcmp(const char *s1, const char *s2, const char *label) {
  ASSERT_EQ(ft_strcmp(s1, s2), strcmp(s1, s2), label);
}

int main(void) {
  {
    ASSERT_EQ(ft_strlen("hello, world"), 12, "ft_strlen should work");
    ASSERT_EQ(ft_strlen(""), 0, "ft_strlen should work with empty strings");
  }

  {
    char *s = calloc(128, sizeof(const char));
    const char *o =
        "Violence is the last refuge of the incompetent - Isaac Asimov";
    const char *sn = ft_strcpy(s, o);
    ASSERT_EQ(*sn, *o, "ft_strcpy should work");
    ASSERT_EQ(sn, s, "ft_strcpy should return dst");
    free(s);
  }

  {
    comp_ft_strcmp("hello", "hella", "ft_strcmp should handle positive diff");
    comp_ft_strcmp("hella", "hello", "ft_strcmp should handle negative diff");
    comp_ft_strcmp("", "", "ft_strcmp should handle equality");
  }

  {
    ssize_t ret;

    ret = ft_write(2, "Testing ft_write...\n", 20);
    ASSERT_EQ(ret, 20, "ft_write should print exact number of characters");

    errno = 0;
    ret = ft_write(-1, "fail", 4);
    ASSERT_EQ(ret, -1, "ft_write should return -1");
    ASSERT_EQ(errno, 9, "ft_write should set errno on error");
  }

  return 0;
}
