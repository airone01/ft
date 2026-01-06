/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:43:39 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 14:55:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"
#include <iostream>
#include <ostream>

// Default constructor
WrongAnimal::WrongAnimal(): _type("WrongAnimal") {
  std::cout << _type << " constructed (default constructor)" << std::endl;
}
// Parameterized constructors
WrongAnimal::WrongAnimal(const std::string &type) : _type(type) {
  std::cout << _type << " constructed (parameterized constructor)" << std::endl;
}
// Copy constructor
WrongAnimal::WrongAnimal(const WrongAnimal &other) : _type(other._type) {
  std::cout << _type << " constructed (copy constructor)" << std::endl;
}
// Destructor
WrongAnimal::~WrongAnimal() { std::cout << _type << " died :'(" << std::endl; }

// Copy asignment operator
WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other) {
  if (this != &other) {
    this->_type = other.getType();
  }
  return (*this);
}

// Getters
const std::string WrongAnimal::getType(void) const { return _type; }

// Private functions
void WrongAnimal::makeSound(void) const {
  std::cout << "I don't know what wrong animal sound to make!" << std::endl;
}
