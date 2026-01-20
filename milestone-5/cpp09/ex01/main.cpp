#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " <RPN expression>" << std::endl;
    return 1;
  }

  if (std::string(argv[1]).find_first_not_of(" \t0123456789+-*/") !=
      std::string::npos) {
    std::cerr << "error: illegal character" << std::endl;
    return 1;
  }

  return 0;
}
