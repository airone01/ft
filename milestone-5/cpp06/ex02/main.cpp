#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

/*
 * @see https://stackoverflow.com/a/332086/11609642
 * @note typeinfo is forbiddn
 */

/**
 * @brief randomly instanciates A, B or C and returns a Base pointer.
 */
Base *generate(void) {
  srand((unsigned)time(NULL));
  int idx = rand() % 3;

  Base b = Base();
  Base *p = &b;

  switch (idx) {
  case 0: {
    A a;
    p = dynamic_cast<Base *>(&a);
    break;
  }
  case 1: {
    B b;
    p = dynamic_cast<Base *>(&b);
    break;
  }
  case 2: {
    C c;
    p = dynamic_cast<Base *>(&c);
    break;
  }
  default:
    std::cerr << "number err" << std::endl;
    p = 0;
    break;
  }

  return p;
}

/**
 * @brief Prints the actual type of the base object
 */
void identify(Base *p) {
  std::cout << "identify(Base *): ";
  if (dynamic_cast<A *>(p))
    std::cout << "Type is A" << std::endl;
  else if (dynamic_cast<B *>(p))
    std::cout << "Type is B" << std::endl;
  else if (dynamic_cast<C *>(p))
    std::cout << "Type is C" << std::endl;
}

/**
 * @brief Prints the actual type of the base object
 * @note Subject says pointers are forbidden in this function
 */
void identify(Base &p) {
  std::cout << "identify(Base *): ";
  if (dynamic_cast<A *>(p))
    std::cout << "Type is A" << std::endl;
  else if (dynamic_cast<B *>(p))
    std::cout << "Type is B" << std::endl;
  else if (dynamic_cast<C *>(p))
    std::cout << "Type is C" << std::endl;
}

int main(void) {
  Base *p = generate();
  identify(p);
  return 0;
}
