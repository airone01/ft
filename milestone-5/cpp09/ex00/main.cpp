#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "error: bad arguments." << std::endl;
    return 1;
  }

  BitcoinExchange btc;

  try {
    btc.loadDatabase("data.csv");
    btc.processInput(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
