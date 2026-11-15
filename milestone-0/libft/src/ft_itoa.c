#include "libft.h"
#include <stddef.h>

static long get_num_len(int n, const char *b) {
  long len = 0;
  long blen = (long)ft_strlen(b);
  long long num;

  if (n <= 0)
    len = 1;
  num = n;
  if (n < 0)
    num = -num;
  while (num > 0) {
    num /= blen;
    len++;
  }
  return (len);
}

static void fill_number(char *s, int n, long len, const char *b) {
  long blen = (long)ft_strlen(b);
  long long num = n;
  int neg = (n < 0);

  if (neg)
    num = -num;
  s[len] = '\0';
  while (len > neg) {
    len--;
    s[len] = b[num % blen];
    num /= blen;
  }
  if (neg)
    s[0] = '-';
}

char *ft_itoa_base(int n, const char *b) {
  long len;
  char *s;

  if (!b)
    return (NULL);
  len = get_num_len(n, b);
  s = ft_calloc((size_t)(len + 1), sizeof(char));
  if (!s)
    return (0);
  fill_number(s, n, len, b);
  return (s);
}

char *ft_itoa(int n) { return (ft_itoa_base(n, "0123456789")); }
