/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:31:30 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/05 10:39:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <fstream>
#include <iostream>

ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("Shrubbery Creation Form", 145, 137), _target("default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("Shrubbery Creation Form", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
    : AForm(other), _target(other._target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm &
ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
  if (this != &other) {
    AForm::operator=(other);
    _target = other._target;
  }
  return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
  if (!this->isSigned())
    throw AForm::FormNotSignedException();
  if (executor.getGrade() > this->getMinExecutionGrade())
    throw AForm::GradeTooLowException();

  std::ofstream outfile((_target + "_shrubbery").c_str());
  if (!outfile) {
    std::cerr << "Error: could not create file." << std::endl;
    return;
  }
  outfile << "       _-_" << std::endl;
  outfile << "    /~~   ~~\\" << std::endl;
  outfile << " /~~         ~~\\" << std::endl;
  outfile << "{               }" << std::endl;
  outfile << " \\  _-     -_  /" << std::endl;
  outfile << "   ~  \\\\ //  ~" << std::endl;
  outfile << "_- -   | | _- _" << std::endl;
  outfile << "  _ -  | |   -_" << std::endl;
  outfile << "      // \\\\" << std::endl;
  outfile.close();
}
