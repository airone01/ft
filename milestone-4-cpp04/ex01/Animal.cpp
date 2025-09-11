/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:20:39 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 14:55:45 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include <iostream>
#include <ostream>

// Default constructor
Animal::Animal(void) : _type("Animal") {
  std::cout << _type << " constructed (default constructor)" << std::endl;
};
// Parameterized constructors
Animal::Animal(const std::string &type) : _type(type) {
  std::cout << _type << " constructed (parameterized constructor)" << std::endl;
}
// Copy constructor
Animal::Animal(const Animal &other) : _type(other._type) {
  std::cout << _type << " constructed (copy constructor)" << std::endl;
};
// Destructor
Animal::~Animal(void) { std::cout << _type << " died :'(" << std::endl; }

// Copy asignment operator
Animal &Animal::operator=(const Animal &other) {
  if (this != &other)
    this->_type = other.getType();
  return (*this);
}

// Getters
const std::string Animal::getType(void) const { return _type; }

// Private functions
void Animal::makeSound(void) const {
  std::cout << "I don't know what animal sound to make!" << std::endl;
}
