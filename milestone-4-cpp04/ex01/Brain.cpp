/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:16:59 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 15:18:14 by elagouch         ###   ########.fr       */
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

// Utility methods
void Brain::setIdea(int index, const std::string &idea) {
  if (index >= 0 && index < 100) {
    _ideas[index] = idea;
  }
}

const std::string &Brain::getIdea(int index) const {
  if (index >= 0 && index < 100) {
    return _ideas[index];
  }
  static std::string empty = "";
  return empty;
}

void Brain::printIdeas(int count) const {
  if (count > 100)
    count = 100;
  std::cout << "Brain ideas: ";
  for (int i = 0; i < count; i++) {
    if (i > 0)
      std::cout << ", ";
    std::cout << "\"" << _ideas[i] << "\"";
  }
  std::cout << std::endl;
}
