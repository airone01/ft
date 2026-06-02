
#include "Brain.hpp"
#include <iostream>
#include <ostream>

// Default constructor
Brain::Brain() {
  std::cout << "Brain : Default Constructor Called" << std::endl;
}
// Copy constructor
Brain::Brain(Brain const &other) {
  for (int i = 0; i < 100; i++) {
    _ideas[i] = other._ideas[i];
  }
}
// Destructor
Brain::~Brain() { std::cout << "Brain : Destructor Called" << std::endl; }

// Copy assignment operator
Brain &Brain::operator=(const Brain &other) {
  std::cout << "Copy Assignment Operator Called" << std::endl;
  if (this != &other) {
    for (int i = 0; i < 100; i++) {
      _ideas[i] = other._ideas[i];
    }
  }
  return *this;
}
