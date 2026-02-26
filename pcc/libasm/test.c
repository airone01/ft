#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ASSERT_EQ(actual, expected, label)                                     \
  do {                                                                         \
    if ((actual) == (expected)) {                                              \
      printf("\033[32mok\033[0m %s\n", label);                                 \
    } else {                                                                   \
      printf("\033[31mKO\033[0m %s (line %d): Expected %ld, got %ld\n", label, \
             __LINE__, (long)(expected), (long)(actual));                      \
    }                                                                          \
  } while (0)

extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(const char *dest, const char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fildes, const void *buf, size_t nbyte);
extern ssize_t ft_read(int fildes, void *buf, size_t nbyte);
extern char *ft_strdup(const char *s);

void comp_ft_strcmp(const char *s1, const char *s2, const char *label) {
  int my_res = ft_strcmp(s1, s2);
  int std_res = strcmp(s1, s2);

  int my_sign = (my_res > 0) - (my_res < 0);
  int std_sign = (std_res > 0) - (std_res < 0);

  ASSERT_EQ(my_sign, std_sign, label);
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
    ASSERT_EQ(sn, s, "ft_strcpy should return dest");
    free(s);
  }

  {
    comp_ft_strcmp("hello", "hella", "ft_strcmp should handle positive diff");
    comp_ft_strcmp("hella", "hello", "ft_strcmp should handle negative diff");
    comp_ft_strcmp("", "", "ft_strcmp should handle equality");
  }

  {
    int fd = open("/dev/null", O_WRONLY);
    if (fd != -1) {
      ASSERT_EQ(ft_write(fd, "Testing ft_write...\n", 20), 20,
                "ft_write should print exact number of characters");

      errno = 0;
      ASSERT_EQ(ft_write(-1, "fail", 4), -1, "ft_write should return -1");
      ASSERT_EQ(errno, 9, "ft_write should set errno on error");
      close(fd);
    } else
      printf("skip: could not open() to test valid write\n");
  }

  {
    char buf[50];
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd != -1) {
      ssize_t ret = ft_read(fd, buf, 10);
      ASSERT_EQ(ret, 10, "ft_read should work");
      close(fd);
    } else
      printf("skip: could not open() to test valid read\n");

    errno = 0;
    ssize_t ret2 = ft_read(-1, buf, 10);
    ASSERT_EQ(ret2, -1, "ft_read should error out properly");
    ASSERT_EQ(errno, EBADF, "ft_read should set errno on error");
  }

  return 0;
}
