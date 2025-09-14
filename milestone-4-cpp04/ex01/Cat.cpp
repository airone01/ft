/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:30:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 13:00:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include <iostream>
#include <ostream>

// Default constructor
Cat::Cat(void) : Animal("Cat") { _brain = new Brain(); };
// Copy constructor
Cat::Cat(const Cat &other) : Animal(other) {
  _brain = new Brain(*other._brain);
};
// Destructor
Cat::~Cat(void) { delete _brain; }

// Copy assignment operator
Cat &Cat::operator=(const Cat &other) {
  if (this != &other) {
    Animal::operator=(other);
    *_brain = *other._brain;
  }
  return *this;
}

// Getters
const std::string Cat::getType(void) const { return _type; }
Brain *Cat::getBrain(void) const { return _brain; }

// Private functions
void Cat::makeSound(void) const { std::cout << "Meow!" << std::endl; }
