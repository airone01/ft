/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:30:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/14 12:33:36 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include <iostream>
#include <ostream>

// Default constructor
Dog::Dog(void) : AAnimal("Dog") { _brain = new Brain(); };
// Copy constructor
Dog::Dog(const Dog &other) : AAnimal(other) {
  _brain = new Brain(*other._brain);
};
// Destructor
Dog::~Dog(void) { delete _brain; }

// Copy assignment operator
Dog &Dog::operator=(const Dog &other) {
  if (this != &other) {
    AAnimal::operator=(other);
    *_brain = *other._brain;
  }
  return *this;
}

// Getters
const std::string Dog::getType(void) const { return _type; }
Brain *Dog::getBrain(void) const { return _brain; }

// Private functions
void Dog::makeSound(void) const { std::cout << "Woof!" << std::endl; }
