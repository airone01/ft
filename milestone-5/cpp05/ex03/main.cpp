#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <iostream>

int main() {
  Intern someRandomIntern;
  Bureaucrat boss("Boss", 1);
  AForm *rrf;
  AForm *scf;
  AForm *wrong;

  std::cout << "--- TEST 1: Create Robotomy Request ---" << std::endl;
  rrf = someRandomIntern.makeForm("robotomy request", "Bender");
  if (rrf) {
    boss.signForm(*rrf);
    boss.executeForm(*rrf);
    delete rrf; // Clean up memory
  }

  std::cout << "\n--- TEST 2: Create Shrubbery Creation ---" << std::endl;
  scf = someRandomIntern.makeForm("shrubbery creation", "Home");
  if (scf) {
    boss.signForm(*scf);
    boss.executeForm(*scf);
    delete scf; // Clean up memory
  }

  std::cout << "\n--- TEST 3: Create Invalid Form ---" << std::endl;
  // This should print an error message and return NULL
  wrong = someRandomIntern.makeForm("coffee making", "Office");
  if (wrong) {
    boss.signForm(*wrong);
    delete wrong;
  } else {
    std::cout << "Pointer is NULL, handled correctly." << std::endl;
  }

  return 0;
}
