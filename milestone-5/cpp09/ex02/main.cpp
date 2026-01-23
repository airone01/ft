#include "PmergeMe.hpp"
#include <exception>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " <positive integer sequence>"
              << std::endl;
    return 1;
  }

  try {
    // parse
    PmergeMe<std::vector> p(argv[1]);

    std::cout << "Before: " << p.getData() << std::endl;

    // TODO: timer start

    // TODO: timer end

    // TODO: timer start
    // TODO: FJ sort deq
    // TODO: timer end

    std::cout << "After : " << p.getData() << std::endl;
    // TODO: display time taken for vec
    // TODO: display time taken for deq
  } catch (const std::exception &e) {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
