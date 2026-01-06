/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:38:19 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/05 10:38:44 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  std::srand(std::time(NULL)); // seed for Robotomy

  Bureaucrat bob("Bob", 1);
  Bureaucrat intern("Intern", 150);

  ShrubberyCreationForm shrub("home");
  RobotomyRequestForm robot("Bender");
  PresidentialPardonForm pardon("Arthur Dent");

  std::cout << "\n--- TEST 1: Unsigned Execution ---" << std::endl;
  bob.executeForm(shrub); // should fail (not signed)

  std::cout << "\n--- TEST 2: Signing and Executing Shrubbery ---" << std::endl;
  bob.signForm(shrub);
  bob.executeForm(shrub); // should create home_shrubbery file

  std::cout << "\n--- TEST 3: Low Grade Failure ---" << std::endl;
  intern.signForm(robot);    // fail
  intern.executeForm(robot); // fail

  std::cout << "\n--- TEST 4: Robotomy (50% chance) ---" << std::endl;
  bob.signForm(robot);
  bob.executeForm(robot);
  bob.executeForm(robot);
  bob.executeForm(robot);

  std::cout << "\n--- TEST 5: Presidential Pardon ---" << std::endl;
  bob.signForm(pardon);
  bob.executeForm(pardon);

  return 0;
}
