/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:30:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/27 16:19:42 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>
#include <ostream>

int main() {
  std::cout << "=== FragTrap Tests ===" << std::endl;

  std::cout << "\n--- Default Constructor ---" << std::endl;
  FragTrap defaultBot;
  defaultBot.highFivesGuys();

  std::cout << "\n--- Named Constructor ---" << std::endl;
  FragTrap namedBot("Destroyer");

  std::cout << "\n--- Copy Constructor ---" << std::endl;
  FragTrap copiedBot(namedBot);

  std::cout << "\n--- Basic Actions ---" << std::endl;
  namedBot.attack("Enemy");
  namedBot.takeDamage(30);
  namedBot.beRepaired(15);
  namedBot.highFivesGuys();

  std::cout << "\n--- Energy Test ---" << std::endl;
  FragTrap energyBot("EnergyTest");
  for (int i = 0; i < 101; i++) {
    energyBot.attack("Target");
  }
  energyBot.highFivesGuys();

  std::cout << "\n--- End of Tests (destructors will be called) ---"
            << std::endl;
  return 0;
}
