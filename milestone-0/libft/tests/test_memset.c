#include "test.h"

int main(void) {
  char buf[32];
  memset(buf, 'A', sizeof(buf));

  void *ret = ft_memset(buf + 4, 'B', 8);
  assert(ret == buf + 4);

  // Check prefix untouched
  for (int i = 0; i < 4; i++) {
    assert(buf[i] == 'A');
  }
  // Check modified range
  for (int i = 4; i < 12; i++) {
    assert(buf[i] == 'B');
  }
  // Check suffix untouched
  for (int i = 12; i < 32; i++) {
    assert(buf[i] == 'A');
  }

  // Zero length memset does nothing
  ret = ft_memset(buf, 'Z', 0);
  assert(ret == buf);
  assert(buf[0] == 'A');

  return 0;
}
