#include "test.h"

int main(void) {
  char buf[32];
  memset(buf, 0xFF, sizeof(buf));

  ft_bzero(buf + 5, 10);

  for (int i = 0; i < 5; i++) {
    assert((unsigned char)buf[i] == 0xFF);
  }
  for (int i = 5; i < 15; i++) {
    assert(buf[i] == 0);
  }
  for (int i = 15; i < 32; i++) {
    assert((unsigned char)buf[i] == 0xFF);
  }

  // 0 length bzero
  ft_bzero(buf, 0);
  assert((unsigned char)buf[0] == 0xFF);

  return 0;
}
