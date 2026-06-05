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
extern int ft_atoi_base(char *str, char *base);
extern int g_invalid_base;
extern int g_no_match;

typedef struct s_list {
  void *data;
  struct s_list *next;
} t_list;

extern void ft_list_push_front(t_list **begin_list, void *data);
extern int ft_list_size(t_list *begin_list);
extern void ft_list_sort(t_list **begin_list, int (*cmp)());
extern void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(),
                              void (*free_fct)(void *));

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
        "Violence is the last refuge of the incompetent — Isaac Asimov";
    const char *sn = ft_strcpy(s, o);

    ASSERT_EQ(strcmp(sn, o), 0, "ft_strcpy should copy full string");
    ASSERT_EQ(sn, s, "ft_strcpy should return dest");
    char dest_buf[10] = "overwrite";
    ft_strcpy(dest_buf, "");
    ASSERT_EQ(dest_buf[0], '\0', "ft_strcpy (empty) should place NUL");
    ASSERT_EQ(dest_buf[1], 'v',
              "ft_strcpy (empty) should not overwrite past NUL");

    free(s);
  }

  {
    comp_ft_strcmp("hello", "hella", "ft_strcmp should handle positive diff");
    comp_ft_strcmp("hella", "hello", "ft_strcmp should handle negative diff");
    comp_ft_strcmp("", "", "ft_strcmp should handle equality");
    comp_ft_strcmp("\xff", "\x01", "ft_strcmp should compare as unsigned char");
    comp_ft_strcmp("ᓚᘏᗢ", "ᓚᘏᗢ", "ft_strcmp should handle special characters");
    // well it should really not make any difference for 'special' characters or
    // not, but I like the cat :-)
  }

  {
    int fd = open("/dev/null", O_WRONLY);
    if (fd != -1) {
      ASSERT_EQ(ft_write(fd, "Testing ft_write...\n", 20), 20,
                "ft_write should print exact number of characters");
      ASSERT_EQ(ft_write(fd, "fail", 0), 0,
                "ft_write with 0 bytes should return 0");
      close(fd);
    } else
      printf("skip: could not open() to test valid write\n");

    errno = 0;
    ASSERT_EQ(ft_write(-1, "fail", 4), -1,
              "ft_write should return -1 on error");
    ASSERT_EQ(errno, EBADF, "ft_write should set errno on error");
  }

  {
    char buf[50];
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd != -1) {
      ssize_t ret = ft_read(fd, buf, 10);
      ASSERT_EQ(ret, 10, "ft_read should work");
      ASSERT_EQ(ft_read(fd, buf, 0), 0, "ft_read with 0 bytes should return 0");
      close(fd);
    } else
      printf("skip: could not open() to test valid read\n");

    errno = 0;
    ssize_t ret2 = ft_read(-1, buf, 10);
    ASSERT_EQ(ret2, -1, "ft_read should error out properly");
    ASSERT_EQ(errno, EBADF, "ft_read should set errno on error");
  }

  {
    const char *orig1 =
        "A language that doesn't have everything is actually "
        "easier to program in than some that do — Dennis Ritchie";
    char *dup1 = ft_strdup(orig1);
    ASSERT_EQ(dup1 != orig1, 1,
              "ft_strdup should allocate a new memory address");
    ASSERT_EQ(strcmp(dup1, orig1), 0,
              "ft_strdup should copy the exact contents");
    free(dup1);

    const char *orig2 = "";
    char *dup2 = ft_strdup(orig2);
    ASSERT_EQ(dup2 != orig2, 1,
              "ft_strdup (empty str) should still allocate new memory");
    ASSERT_EQ(strcmp(dup2, orig2), 0,
              "ft_strdup (empty str) should cleanly copy the NUL terminator");
    free(dup2);
  }

  {
#define RESET_FLAGS()                                                          \
  do {                                                                         \
    g_invalid_base = 0;                                                        \
    g_no_match = 0;                                                            \
  } while (0)

    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("123", "0123456789"), 123,
              "ft_atoi_base: decimal positive");
    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("-456", "0123456789"), -456,
              "ft_atoi_base: decimal negative");
    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("+42", "0123456789"), 42,
              "ft_atoi_base: explicit positive sign");
    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("  \t 99", "0123456789"), 99,
              "ft_atoi_base: leading whitespace");
    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("  -7", "0123456789"), -7,
              "ft_atoi_base: whitespace then minus");
    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("++--9", "0123456789"), 9,
              "ft_atoi_base: double negation cancels out");
    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("0", "0123456789"), 0, "ft_atoi_base: zero");
    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("ff", "0123456789abcdef"), 255,
              "ft_atoi_base: hex ff");
    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("-ff", "0123456789abcdef"), -255,
              "ft_atoi_base: hex negative");
    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("10", "01"), 2, "ft_atoi_base: binary 10 = 2");
    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("1111", "01"), 15, "ft_atoi_base: binary 1111 = 15");
    RESET_FLAGS();
    ASSERT_EQ(ft_atoi_base("z", "0z"), 1, "ft_atoi_base: custom two-char base");

    /* invalid base: too short */
    RESET_FLAGS();
    ft_atoi_base("1", "0");
    ASSERT_EQ(g_invalid_base, 1,
              "ft_atoi_base: base len 1 sets g_invalid_base");

    /* invalid base: contains '+' */
    RESET_FLAGS();
    ft_atoi_base("1", "0+1");
    ASSERT_EQ(g_invalid_base, 1,
              "ft_atoi_base: base with '+' sets g_invalid_base");

    /* invalid base: contains '-' */
    RESET_FLAGS();
    ft_atoi_base("1", "0-1");
    ASSERT_EQ(g_invalid_base, 1,
              "ft_atoi_base: base with '-' sets g_invalid_base");

    /* invalid base: contains space */
    RESET_FLAGS();
    ft_atoi_base("1", "0 1");
    ASSERT_EQ(g_invalid_base, 1,
              "ft_atoi_base: base with ' ' sets g_invalid_base");

    /* invalid base: duplicate chars */
    RESET_FLAGS();
    ft_atoi_base("1", "001");
    ASSERT_EQ(g_invalid_base, 1,
              "ft_atoi_base: duplicate base chars sets g_invalid_base");

    /* no match: char not in base */
    RESET_FLAGS();
    ft_atoi_base("9", "01234567");
    ASSERT_EQ(g_no_match, 1,
              "ft_atoi_base: digit outside base sets g_no_match");

    /* no match: char mid-string not in base */
    RESET_FLAGS();
    ft_atoi_base("12x4", "0123456789");
    ASSERT_EQ(g_no_match, 1,
              "ft_atoi_base: mid-string invalid char sets g_no_match");
  }

  {
    t_list *list = NULL;

    /* ft_list_size: NULL list */
    ASSERT_EQ(ft_list_size(NULL), 0, "ft_list_size: empty list returns 0");

    /* ft_list_push_front: single push */
    ft_list_push_front(&list, "hello");
    ASSERT_EQ(ft_list_size(list), 1,
              "ft_list_push_front: size is 1 after one push");
    ASSERT_EQ(strcmp((char *)list->data, "hello"), 0,
              "ft_list_push_front: data of first node is correct");

    /* ft_list_push_front: second push goes to front */
    ft_list_push_front(&list, "world");
    ASSERT_EQ(ft_list_size(list), 2,
              "ft_list_push_front: size is 2 after two pushes");
    ASSERT_EQ(strcmp((char *)list->data, "world"), 0,
              "ft_list_push_front: new node is at front");
    ASSERT_EQ(strcmp((char *)list->next->data, "hello"), 0,
              "ft_list_push_front: old node is second");

    /* ft_list_push_front: third push */
    ft_list_push_front(&list, "!");
    ASSERT_EQ(ft_list_size(list), 3, "ft_list_size: three-element list");

    /* ft_list_sort: sort ["!", "world", "hello"] ascending by strcmp */
    ft_list_sort(&list, (int (*)())ft_strcmp);
    ASSERT_EQ(strcmp((char *)list->data, "!"), 0,
              "ft_list_sort: first element after sort");
    ASSERT_EQ(strcmp((char *)list->next->data, "hello"), 0,
              "ft_list_sort: second element after sort");
    ASSERT_EQ(strcmp((char *)list->next->next->data, "world"), 0,
              "ft_list_sort: third element after sort");

    /* ft_list_sort: already-sorted list is stable */
    ft_list_sort(&list, (int (*)())ft_strcmp);
    ASSERT_EQ(strcmp((char *)list->data, "!"), 0,
              "ft_list_sort: already-sorted list unchanged");

    /* free the sorted list before remove_if tests */
    while (list) {
      t_list *n = list->next;
      free(list);
      list = n;
    }

    /* ft_list_remove_if: build ["a", "b", "a", "c"] using strdup data */
    list = NULL;
    ft_list_push_front(&list, strdup("c"));
    ft_list_push_front(&list, strdup("a"));
    ft_list_push_front(&list, strdup("b"));
    ft_list_push_front(&list, strdup("a"));
    /* list is now: a -> b -> a -> c */

    /* remove all "a" nodes */
    ft_list_remove_if(&list, "a", (int (*)())ft_strcmp, free);
    ASSERT_EQ(ft_list_size(list), 2,
              "ft_list_remove_if: size is 2 after removing two 'a' nodes");
    ASSERT_EQ(strcmp((char *)list->data, "b"), 0,
              "ft_list_remove_if: first remaining node is 'b'");
    ASSERT_EQ(strcmp((char *)list->next->data, "c"), 0,
              "ft_list_remove_if: second remaining node is 'c'");

    /* remove all remaining nodes */
    ft_list_remove_if(&list, "b", (int (*)())ft_strcmp, free);
    ft_list_remove_if(&list, "c", (int (*)())ft_strcmp, free);
    ASSERT_EQ(list, NULL,
              "ft_list_remove_if: list is NULL after removing all nodes");
  }

  return 0;
}
