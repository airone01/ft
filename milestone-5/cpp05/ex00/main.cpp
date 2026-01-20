#include "Bureaucrat.hpp"
#include <iostream>

int main() {
  // Test valid construction and printing
  try {
    Bureaucrat bob("Bob", 75);
    std::cout << bob << std::endl;
  } catch (std::exception &e) {
    std::cerr << "Unexpected exception: " << e.what() << std::endl;
  }

  // Test grade too high in constructor
  try {
    Bureaucrat alice("Alice", 0);
    std::cout << alice << std::endl;
  } catch (Bureaucrat::GradeTooHighException &e) {
    std::cerr << "Caught GradeTooHighException: " << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "Unexpected exception: " << e.what() << std::endl;
  }

  // Test grade too low in constructor
  try {
    Bureaucrat charlie("Charlie", 151);
    std::cout << charlie << std::endl;
  } catch (Bureaucrat::GradeTooLowException &e) {
    std::cerr << "Caught GradeTooLowException: " << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "Unexpected exception: " << e.what() << std::endl;
  }

  // Test increment grade (should decrease number)
  try {
    Bureaucrat dave("Dave", 3);
    std::cout << "Before increment: " << dave << std::endl;
    dave.incrementGrade();
    std::cout << "After increment: " << dave << std::endl;
  } catch (std::exception &e) {
    std::cerr << "Unexpected exception: " << e.what() << std::endl;
  }

  // Test increment beyond limit
  try {
    Bureaucrat eve("Eve", 1);
    std::cout << "Before increment: " << eve << std::endl;
    eve.incrementGrade();
    std::cout << "After increment: " << eve << std::endl;
  } catch (Bureaucrat::GradeTooHighException &e) {
    std::cerr << "Caught GradeTooHighException: " << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "Unexpected exception: " << e.what() << std::endl;
  }

  // Test decrement grade (should increase number)
  try {
    Bureaucrat frank("Frank", 150);
    std::cout << "Before decrement: " << frank << std::endl;
    frank.decrementGrade();
    std::cout << "After decrement: " << frank << std::endl;
  } catch (std::exception &e) {
    std::cerr << "Unexpected exception: " << e.what() << std::endl;
  }

  // Test decrement beyond limit
  try {
    Bureaucrat grace("Grace", 150);
    std::cout << "Before decrement: " << grace << std::endl;
    grace.decrementGrade();
    std::cout << "After decrement: " << grace << std::endl;
  } catch (Bureaucrat::GradeTooLowException &e) {
    std::cerr << "Caught GradeTooLowException: " << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "Unexpected exception: " << e.what() << std::endl;
  }

  // Test edge cases: min and max grades
  try {
    Bureaucrat minGrade("Min", 150);
    std::cout << minGrade << std::endl;
    Bureaucrat maxGrade("Max", 1);
    std::cout << maxGrade << std::endl;
  } catch (std::exception &e) {
    std::cerr << "Unexpected exception: " << e.what() << std::endl;
  }

  return 0;
}
