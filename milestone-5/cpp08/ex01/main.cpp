#include "Span.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

bool assert(bool condition, const std::string &name) {
  if (condition)
    std::cout << "[\x1B[32mOK\033[0m] " << name << std::endl;
  else
    std::cout << "[\x1B[31mKO\033[0m] " << name << std::endl;
  return condition;
}

static unsigned int entry_idx = 0;

int pop_num() { return static_cast<int>(entry_idx++); }
int pop_rand() { return rand() % 10000; }

bool tests() {
  unsigned int _1M = 1000000;
  unsigned int _1k = 1000;
  bool status = false;

  {
    Span sp(_1M);
    std::vector<int> tmp(_1M);
    std::generate(tmp.begin(), tmp.end(), &pop_num);
    sp.insert(tmp.begin(), tmp.end());
    int small = sp.shortestSpan();
    int large = sp.longestSpan();

    if (!assert(small == 1 && large == static_cast<int>(_1M - 1),
                "all nums 0-1M")) {
      std::cerr << "small: " << small << ", long: " << large << std::endl;
      status = true;
    }
  }

  {
    std::srand(42); // same seed always, same result always
    Span sp(_1k);
    std::vector<int> tmp(_1k);
    std::generate(tmp.begin(), tmp.end(), &pop_rand);
    sp.insert(tmp.begin(), tmp.end());
    int small = sp.shortestSpan();
    int large = sp.longestSpan();

    if (!assert(small == 0 && large >= static_cast<int>(_1k - 20),
                "1k pseudo-random nums 0-10k")) {
      std::cerr << "small: " << small << ", long: " << large << std::endl;
      status = true;
    }
  }

  {
    std::srand(static_cast<unsigned int>(std::time(0)));
    Span sp(_1k);
    std::vector<int> tmp(_1k);
    std::generate(tmp.begin(), tmp.end(), &pop_rand);
    sp.insert(tmp.begin(), tmp.end());
    int small = sp.shortestSpan();
    int large = sp.longestSpan();

    if (!assert(small <= 20 && large >= static_cast<int>(_1k - 20),
                "1k random nums 0-10k")) {
      std::cerr << "small: " << small << ", long: " << large << std::endl;
      status = true;
    }
  }

  {
    bool test_threw = false;
    Span sp(0);
    try {
      sp.addNumber(42);
    } catch (const std::exception &e) {
      test_threw = true;
    }

    if (!assert(test_threw, "adding to full Span throws")) {
      status = true;
    }
  }

  return status;
}

int main(void) {
  if (tests()) {
    std::cerr << "Some tests failed." << std::endl;
    return 1;
  }

  return 0;
}
