#include "test.h"

int main(void) {
  // Normal allocation
  size_t count = 32;
  size_t sz = sizeof(int);
  int *arr = (int *)ft_calloc(count, sz);
  assert(arr != NULL);
  for (size_t i = 0; i < count; i++) {
    assert(arr[i] == 0);
  }
  free(arr);

  // nmemb == 0 returns valid pointer that can be freed
  void *p1 = ft_calloc(0, 10);
  assert(p1 != NULL);
  free(p1);

  // size == 0 returns valid pointer that can be freed
  void *p2 = ft_calloc(10, 0);
  assert(p2 != NULL);
  free(p2);

  // Both 0
  void *p3 = ft_calloc(0, 0);
  assert(p3 != NULL);
  free(p3);

  return 0;
}
