
#include "Dog.hpp"
#include <iostream>
#include <ostream>

// Default constructor
Dog::Dog(void) : Animal("Dog") {}
// Copy constructor
Dog::Dog(const Dog &other) : Animal(other) {}
// Destructor
Dog::~Dog(void) {}

// Copy assignment operator
Dog &Dog::operator=(const Dog &other) {
  if (this != &other)
    Animal::operator=(other);
  return *this;
}

// Getters
const std::string Dog::getType(void) const { return _type; }

// Private functions
void Dog::makeSound(void) const { std::cout << "Woof!" << std::endl; }
