/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:40:04 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/12 17:35:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>

const int Fixed::_bits = 8;

// Default constructor
Fixed::Fixed() : _val(0) {
  std::cout << "Default constructor called" << std::endl;
}
// Copy constructor
Fixed::Fixed(const Fixed &other) : _val(other._val) {
  std::cout << "Copy constructor called" << std::endl;
}
// Destructor
Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

// Copy asignment operator
Fixed &Fixed::operator=(const Fixed &other) {
  std::cout << "Copy assignment operator called" << std::endl;
  if (this != &other) {
    setRawBits(other.getRawBits());
  }
  return *this;
}

// Getters
int Fixed::getRawBits(void) const {
  std::cout << "getRawBits member method called" << std::endl;
  return _val;
}

// Setters
void Fixed::setRawBits(int const raw) {
  std::cout << "setRawBits member method called" << std::endl;
  _val = raw;
}
