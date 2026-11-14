#include "test.h"

int main(void) {
  const char *haystack = "Foo Bar Baz";

  // Needle empty -> returns big
  assert(ft_strnstr(haystack, "", 11) == haystack);
  assert(ft_strnstr(haystack, "", 0) == haystack);

  // Match at start
  assert(ft_strnstr(haystack, "Foo", 11) == haystack);
  assert(ft_strnstr(haystack, "Foo", 3) == haystack);
  assert(ft_strnstr(haystack, "Foo", 2) == NULL);

  // Match in middle
  assert(ft_strnstr(haystack, "Bar", 11) == haystack + 4);
  assert(ft_strnstr(haystack, "Bar", 7) == haystack + 4);
  assert(ft_strnstr(haystack, "Bar", 6) == NULL);

  // Match at end
  assert(ft_strnstr(haystack, "Baz", 11) == haystack + 8);
  assert(ft_strnstr(haystack, "Baz", 10) == NULL);

  // Not found
  assert(ft_strnstr(haystack, "Qux", 11) == NULL);

  // Needle longer than haystack
  assert(ft_strnstr("ab", "abcdef", 10) == NULL);

  // Zero len
  assert(ft_strnstr(haystack, "Foo", 0) == NULL);

  return 0;
}
