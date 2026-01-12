#include "iter.hpp"
#include <iostream>
#include <vector>

void my_print(int e) { std::cout << "iterating " << e << std::endl; }

int main(void) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(42);

  iter(&v[0], static_cast<int>(v.size()), my_print);

  return 0;
}
