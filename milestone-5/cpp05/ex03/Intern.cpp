/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:35:28 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/05 13:36:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <iostream>

Intern::Intern() {}

Intern::Intern(const Intern &other) { (void)other; }

Intern::~Intern() {}

Intern &Intern::operator=(const Intern &other) {
  (void)other;
  return *this;
}

// Static helper functions to create specific forms
static AForm *makeShrubbery(const std::string target) {
  return new ShrubberyCreationForm(target);
}

static AForm *makeRobotomy(const std::string target) {
  return new RobotomyRequestForm(target);
}

static AForm *makePresidential(const std::string target) {
  return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(std::string formName, std::string target) {
  std::string formNames[] = {"shrubbery creation", "robotomy request",
                             "presidential pardon"};

  // function pointers to the static helpers related to their respective name
  // string
  AForm *(*formCreators[])(const std::string) = {&makeShrubbery, &makeRobotomy,
                                                 &makePresidential};

  for (int i = 0; i < 3; i++) {
    if (formName == formNames[i]) {
      std::cout << "Intern creates " << formName << std::endl;
      return formCreators[i](target);
    }
  }

  std::cout << "Intern cannot create " << formName
            << " because it doesn't exist." << std::endl;
  return NULL;
}
