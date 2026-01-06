/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:20:39 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/14 12:34:33 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"
#include <iostream>
#include <ostream>

// Default constructor
AAnimal::AAnimal(void) : _type("Animal") {
  std::cout << _type << " constructed (default constructor)" << std::endl;
};
// Parameterized constructors
AAnimal::AAnimal(const std::string &type) : _type(type) {
  std::cout << _type << " constructed (parameterized constructor)" << std::endl;
}
// Copy constructor
AAnimal::AAnimal(const AAnimal &other) : _type(other._type) {
  std::cout << _type << " constructed (copy constructor)" << std::endl;
};
// Destructor
AAnimal::~AAnimal(void) { std::cout << _type << " died :'(" << std::endl; }

// Copy asignment operator
AAnimal &AAnimal::operator=(const AAnimal &other) {
  if (this != &other)
    this->_type = other.getType();
  return (*this);
}

// Getters
const std::string AAnimal::getType(void) const { return _type; }

