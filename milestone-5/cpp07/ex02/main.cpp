#include "Array.hpp"
#include <exception>
#include <iostream>

int main(void) {
  Array<int> a = Array<int>(10);

  std::cout << "TEST 1: array init" << std::endl;
  std::cout << "val a@0 is " << a[0] << ", size is " << a.size() << std::endl;
  std::cout << "(this should not segfault, size should be 10)" << std::endl << std::endl;

  Array<int> b = Array<int>(a);
  b[2] = 100;

  std::cout << "TEST 2: deep copy" << std::endl;
  std::cout << "ptr a@2 is " << &a[2] << ", val is " << a[2] << std::endl;
  std::cout << "ptr b@2 is " << &b[2] << ", val is " << b[2] << std::endl;
  std::cout << "(neither the pointers nor the values should not be equal)" << std::endl << std::endl;

  std::cout << "TEST 3: wrong access" << std::endl;
  try {
    const int bruh = a[100];
    (void)bruh;
  } catch (const std::exception &e) {
    std::cerr << "Exception caught (good): " << e.what() << std::endl;
  }
  std::cout << "(this should throw)" << std::endl << std::endl;

  return 0;
}
