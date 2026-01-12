#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

/*
 * @see https://stackoverflow.com/a/332086/11609642
 * @note type_info is forbidden
 */

/**
 * @brief randomly instanciates A, B or C and returns a Base pointer.
 */
Base *generate(void) {
  srand((unsigned)time(NULL));
  int idx = rand() % 3;

  switch (idx) {
  case 0:
    return new A;
  case 1:
    return new B;
  case 2:
  default:
    return new C;
  }
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
  Base base;
  try {
    base = dynamic_cast<A &>(p);
    std::cout << "Type is A" << std::endl;
  } catch (const std::exception &e) {
  }
  try {
    base = dynamic_cast<B &>(p);
    std::cout << "Type is B" << std::endl;
  } catch (const std::exception &e) {
  }
  try {
    base = dynamic_cast<C &>(p);
    std::cout << "Type is C" << std::endl;
  } catch (const std::exception &e) {
  }
}

int main(void) {
  Base *p = generate();
  identify(p);
  identify(*p);
  return 0;
}
