#include "iter.hpp"
#include <iostream>

void my_print(int e) { std::cout << "iterating " << e << std::endl; }

int main(void) {
  int v[4];
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  v[3] = 42;

  iter(&v[0], 4, my_print);

  return 0;
}
