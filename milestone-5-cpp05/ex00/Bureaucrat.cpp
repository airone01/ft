/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:22:17 by elagouch          #+#    #+#             */
/*   Updated: 2025/10/01 16:00:12 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <iostream>

// canonical

Bureaucrat::Bureaucrat() : _name("Leslie Knope"), _grade(100) {};

Bureaucrat::Bureaucrat(const Bureaucrat &other)
    : _name(other._name), _grade(other._grade) {};

Bureaucrat::~Bureaucrat() {};

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
  if (this != &other) {
    _grade = other._grade;
  }
  return *this;
}

// parameterized constructors

Bureaucrat::Bureaucrat(const std::string name, int grade)
    : _name(name), _grade(grade) {
  if (grade < 1)
    throw GradeTooHighException();
  if (grade > 150)
    throw GradeTooLowException();
};

// getters

const std::string Bureaucrat::getName(void) const { return _name; }

int Bureaucrat::getGrade(void) const { return _grade; }

// setters

void Bureaucrat::incrementGrade(void) {
  if (_grade <= 1)
    throw GradeTooHighException();
  _grade--;
}

void Bureaucrat::decrementGrade(void) {
  if (_grade >= 150)
    throw GradeTooLowException();
  _grade++;
}

// exceptions

const char *Bureaucrat::GradeTooHighException::what(void) const throw() {
  return "Grade is too high!";
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw() {
  return "Grade is too low!";
}

// ostream overload
std::ostream &operator<<(std::ostream &os, const Bureaucrat &bc) {
  os << bc.getName() << ", bureaucrat grade " << bc.getGrade() << ".";
  return os;
};
