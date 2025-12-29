/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:53:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/12/29 12:25:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

Form::Form() : _signed(false), _minSigningGrade(150), _minExecutionGrade(150) {}

Form::Form(const Form &other)
    : _signed(other._signed), _minSigningGrade(other._minSigningGrade),
      _minExecutionGrade(other._minExecutionGrade) {}

Form::~Form() {}

Form &Form::operator=(const Form &other) {
  if (this != &other) {
    _signed = other._signed;
  }
  return *this;
}

Form::Form(const int minSigningGrade, int minExecutionGrade)
    : _signed(false), _minSigningGrade(minSigningGrade),
      _minExecutionGrade(minExecutionGrade) {
  if (minSigningGrade < 1 || minExecutionGrade < 1)
    throw GradeTooHighException();
  if (minSigningGrade > 150 || minExecutionGrade > 150)
    throw GradeTooLowException();
}

bool Form::isSigned() const { return this->_signed; }

int Form::getMinSigningGrade() const { return this->_minSigningGrade; }

int Form::getMinExecutionGrade() const { return this->_minExecutionGrade; }

void Form::beSigned(const Bureaucrat &bc) {
  if (bc.getGrade() > this->getMinSigningGrade())
    throw GradeTooLowException();
  this->_signed = true;
}

void Form::signForm(const Bureaucrat &bc) {
  try {
    this->beSigned(bc);
    std::cout << bc.getName() << " signed " << this;
  } catch (GradeTooLowException e) {
    std::cout << bc.getName() << " couldn't sign " << this << " because "
              << e.what();
  }
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
  os << "Signed: " << fm.isSigned()
     << ", required execution grade: " << fm.getMinExecutionGrade()
     << ", required siggning grade: " << fm.getMinSigningGrade();
  return os;
};
