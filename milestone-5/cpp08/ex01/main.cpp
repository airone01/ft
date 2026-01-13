#include "Span.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

void display_res(const Span &sp) {
  std::cout << "shortest: " << sp.shortestSpan() << std::endl;
  std::cout << "longest:  " << sp.longestSpan() << std::endl;
}

static unsigned int entry_idx = 0;

int pop_num() { return static_cast<int>(entry_idx++); }
int pop_rand() { return rand() % 10000; }

int main(void) {
  std::cout << "TEST 1: All numbers from 0 to 1M" << std::endl;

  unsigned int _1M = 1000000;
  unsigned int _1k = 1000;

  {
    Span sp = Span(_1M);
    std::vector<int> tmp(_1M);
    std::generate(tmp.begin(), tmp.end(), &pop_num);
    sp.insert(tmp.begin(), tmp.end());
    display_res(sp);
    std::cout << "observation: shortest should be 1 and longest close to 1M"
              << std::endl
              << std::endl;
  }

  std::cout << "TEST 2: Random (%10k) 1k numbers (seeded with `42`)"
            << std::endl;

  {
    std::srand(42); // same seed always, same result always
    Span sp = Span(_1k);
    std::vector<int> tmp(_1k);
    std::generate(tmp.begin(), tmp.end(), &pop_rand);
    sp.insert(tmp.begin(), tmp.end());
    display_res(sp);
    std::cout << "observation: shortest should be 0 and longest close to 10k"
              << std::endl
              << std::endl;

    std::cout << "TEST 3: Random (%10k) 1k numbers (seeded with time)"
              << std::endl;
  }

  {
    std::srand(static_cast<unsigned int>(std::time(0)));
    Span sp = Span(_1k);
    std::vector<int> tmp(_1k);
    std::generate(tmp.begin(), tmp.end(), &pop_rand);
    sp.insert(tmp.begin(), tmp.end());
    display_res(sp);
    std::cout
        << "observation: shortest and longest should be close to 0 and 10k "
           "respectively"
        << std::endl
        << std::endl;
  }

  return 0;
}
