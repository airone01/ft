#include "ScalarConverter.hpp"
#include <iostream>
#include <string>

int main() {
  std::string inln;

  // eof
  if (!std::getline(std::cin, inln)) {
    std::cout << std::endl;
    return 0;
  }
  ScalarConverter::convert(inln);

  return 0;
}
