/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:30:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/08 18:49:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include <iostream>
#include <ostream>

// Default constructor
Cat::Cat(void) : Animal("Cat") {};
// Copy constructor
Cat::Cat(const Animal &other) : Animal(other) {};
// Destructor
Cat::~Cat(void) {}

// Private functions
void Cat::makeSound(void) { std::cout << "Meoooow!" << std::endl; }
