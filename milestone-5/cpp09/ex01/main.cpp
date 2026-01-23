#include "RPN.hpp"
#include <exception>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " <RPN expression>" << std::endl;
    return 1;
  }

  try {
    RPN::parse(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << "error: " << e.what() << std::endl;
  }

  return 0;
}
