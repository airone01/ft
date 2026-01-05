/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:35:53 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/05 10:36:03 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm()
    : AForm("Presidential Pardon Form", 25, 5), _target("default") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
    : AForm("Presidential Pardon Form", 25, 5), _target(target) {}

PresidentialPardonForm::PresidentialPardonForm(
    const PresidentialPardonForm &other)
    : AForm(other), _target(other._target) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm &
PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
  if (this != &other) {
    AForm::operator=(other);
    _target = other._target;
  }
  return *this;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const {
  if (!this->isSigned())
    throw AForm::FormNotSignedException();
  if (executor.getGrade() > this->getMinExecutionGrade())
    throw AForm::GradeTooLowException();

  std::cout << _target << " has been pardoned by Zaphod Beeblebrox."
            << std::endl;
}
