/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:30:00 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/12 17:38:44 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include <iostream>
#include <ostream>

// Default constructor
Cat::Cat(void) : AAnimal("Cat") { _brain = new Brain(); }
// Copy constructor
Cat::Cat(const Cat &other) : AAnimal(other) {
  _brain = new Brain(*other._brain);
}
// Destructor
Cat::~Cat(void) { delete _brain; }

// Copy assignment operator
Cat &Cat::operator=(const Cat &other) {
  if (this != &other) {
    AAnimal::operator=(other);
    *_brain = *other._brain;
  }
  return *this;
}

// Getters
const std::string Cat::getType(void) const { return _type; }
Brain *Cat::getBrain(void) const { return _brain; }

// Private functions
void Cat::makeSound(void) const { std::cout << "Meow!" << std::endl; }
