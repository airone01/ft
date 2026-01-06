/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:53:34 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/05 13:40:52 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

AForm::AForm()
    : _name("Formulaire A38"), _signed(false), _minSigningGrade(150),
      _minExecutionGrade(150) {}

AForm::AForm(const AForm &other)
    : _name(other._name), _signed(other._signed),
      _minSigningGrade(other._minSigningGrade),
      _minExecutionGrade(other._minExecutionGrade) {}

AForm::~AForm() {}

AForm &AForm::operator=(const AForm &other) {
  if (this != &other) {
    _signed = other._signed;
  }
  return *this;
}

AForm::AForm(std::string name, int minSigningGrade, int minExecutionGrade)
    : _name(name), _signed(false), _minSigningGrade(minSigningGrade),
      _minExecutionGrade(minExecutionGrade) {
  if (minSigningGrade < 1 || minExecutionGrade < 1)
    throw GradeTooHighException();
  if (minSigningGrade > 150 || minExecutionGrade > 150)
    throw GradeTooLowException();
}

std::string AForm::getName() const { return this->_name; }

bool AForm::isSigned() const { return this->_signed; }

int AForm::getMinSigningGrade() const { return this->_minSigningGrade; }

int AForm::getMinExecutionGrade() const { return this->_minExecutionGrade; }

void AForm::beSigned(Bureaucrat &bc) {
  if (bc.getGrade() > this->getMinSigningGrade())
    throw GradeTooLowException();
  this->_signed = true;
}

// exceptions
const char *AForm::GradeTooHighException::what(void) const throw() {
  return "Grade is too high!";
}

const char *AForm::GradeTooLowException::what(void) const throw() {
  return "Grade is too low!";
}

const char *AForm::FormNotSignedException::what() const throw() {
  return "Form is not signed!";
}

// ostream overload
std::ostream &operator<<(std::ostream &os, const AForm &fm) {
  os << "Form " << fm.getName()
     << ", signed: " << (fm.isSigned() ? "yes" : "no")
     << ", sign grade: " << fm.getMinSigningGrade()
     << ", exec grade: " << fm.getMinExecutionGrade() << std::endl;
  return os;
};
