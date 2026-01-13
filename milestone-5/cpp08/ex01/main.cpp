#include "Span.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

void display_res(const Span &sp) {
  std::cout << "shortest: " << sp.shortestSpan() << std::endl;
  std::cout << "longest:  " << sp.longestSpan() << std::endl;
}

int pop_num(unsigned int i) { return static_cast<int>(i); }
int pop_rand(unsigned int i) {
  (void)i;
  return rand() % 10000;
}

int main(void) {
  std::cout << "TEST 1: All numbers from 0 to 20k" << std::endl;

  Span sp1 = Span(20000);
  sp1.populate(20000, &pop_num);
  display_res(sp1);
  std::cout << "observation: smallest should be 1 and biggest 20k-1"
            << std::endl
            << std::endl;

  std::cout << "TEST 2: Random (%10k) 1k numbers (seeded with `42`)"
            << std::endl;

  std::srand(42); // same seed always, same result always
  Span sp2 = Span(10000);
  sp2.populate(10000, &pop_rand);
  display_res(sp2);
  std::cout << "observation: smallest should be 0 and biggest close to 10k-1"
            << std::endl
            << std::endl;

  std::cout << "TEST 3: Random (%10k) 1k numbers (seeded with time)"
            << std::endl;

  std::srand(static_cast<unsigned int>(std::time(0)));
  Span sp3 = Span(10000);
  for (unsigned int i = 0; i < 1000; i++)
    sp3.addNumber(static_cast<int>(std::rand() % 10000));
  display_res(sp3);
  std::cout << "observation: smallest and biggest should be close to 0 and 10k "
               "respectively"
            << std::endl
            << std::endl;

  return 0;
}
