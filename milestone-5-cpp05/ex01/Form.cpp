/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:53:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/12/29 12:44:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

Form::Form()
    : _name("Formulaire A38"), _signed(false), _minSigningGrade(150),
      _minExecutionGrade(150) {}

Form::Form(const Form &other)
    : _name(other._name), _signed(other._signed),
      _minSigningGrade(other._minSigningGrade),
      _minExecutionGrade(other._minExecutionGrade) {}

Form::~Form() {}

Form &Form::operator=(const Form &other) {
  if (this != &other) {
    _name = other._name;
    _signed = other._signed;
  }
  return *this;
}

Form::Form(std::string name, const int minSigningGrade, int minExecutionGrade)
    : _name(name), _signed(false), _minSigningGrade(minSigningGrade),
      _minExecutionGrade(minExecutionGrade) {
  if (minSigningGrade < 1 || minExecutionGrade < 1)
    throw GradeTooHighException();
  if (minSigningGrade > 150 || minExecutionGrade > 150)
    throw GradeTooLowException();
}

std::string Form::getName() const { return this->_name; }

bool Form::isSigned() const { return this->_signed; }

int Form::getMinSigningGrade() const { return this->_minSigningGrade; }

int Form::getMinExecutionGrade() const { return this->_minExecutionGrade; }

void Form::beSigned(Bureaucrat &bc) {
  if (bc.getGrade() > this->getMinSigningGrade())
    throw GradeTooLowException();
  this->_signed = true;
}

// exceptions
const char *Form::GradeTooHighException::what(void) const throw() {
  return "Grade is too high!";
}

const char *Form::GradeTooLowException::what(void) const throw() {
  return "Grade is too low!";
}

// ostream overload
std::ostream &operator<<(std::ostream &os, const Form &fm) {
  os << fm.getName();
  return os;
};
