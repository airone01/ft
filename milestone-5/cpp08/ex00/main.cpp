#include "easyfind.hpp"
#include <exception>
#include <iostream>
#include <vector>

int main(void) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(42);

  try {
    std::cout << "found " << easyfind(v, 42) << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "failed: " << e.what() << std::endl;
  }

  return 0;
}
