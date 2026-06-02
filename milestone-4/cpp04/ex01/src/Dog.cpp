
#include "Dog.hpp"
#include <iostream>
#include <ostream>

// Default constructor
Dog::Dog(void) : Animal("Dog") { _brain = new Brain(); }
// Copy constructor
Dog::Dog(const Dog &other) : Animal(other) {
  _brain = new Brain(*other._brain);
}
// Destructor
Dog::~Dog(void) { delete _brain; }

// Copy assignment operator
Dog &Dog::operator=(const Dog &other) {
  if (this != &other) {
    Animal::operator=(other);
    *_brain = *other._brain;
  }
  return *this;
}

// Getters
const std::string Dog::getType(void) const { return _type; }
Brain *Dog::getBrain(void) const { return _brain; }

// Private functions
void Dog::makeSound(void) const { std::cout << "Woof!" << std::endl; }
