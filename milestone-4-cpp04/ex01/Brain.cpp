/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:16:59 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/12 16:22:51 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"
#include <iostream>
#include <ostream>

// Default constructor
Brain::Brain() {
  std::cout << "Brain : Default Constructor Called" << std::endl;
}
// Copy constructor
Brain::Brain(Brain const &other) {
  for (int i = 0; i < 100; i++) {
    _ideas[i] = other._ideas[i];
  }
}
// Destructor
Brain::~Brain() { std::cout << "Brain : Destructor Called" << std::endl; }

// Copy assignment operator
Brain &Brain::operator=(const Brain &other) {
  std::cout << "Copy Assignment Operator Called" << std::endl;
  if (this != &other) {
    for (int i = 0; i < 100; i++) {
      _ideas[i] = other._ideas[i];
    }
  }
  return *this;
}

