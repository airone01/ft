
#include "ScavTrap.hpp"

#include <iostream>
#include <ostream>

int main() {
  std::cout << "=== ScavTrap Tests ===" << std::endl;

  std::cout << "\n--- Default Constructor ---" << std::endl;
  ScavTrap defaultBot;
  defaultBot.guardGate();

  std::cout << "\n--- Named Constructor ---" << std::endl;
  ScavTrap namedBot("Destroyer");

  std::cout << "\n--- Copy Constructor ---" << std::endl;
  ScavTrap copiedBot(namedBot);

  std::cout << "\n--- Basic Actions ---" << std::endl;
  namedBot.attack("Enemy");
  namedBot.takeDamage(30);
  namedBot.beRepaired(15);
  namedBot.guardGate();

  std::cout << "\n--- Energy Test ---" << std::endl;
  ScavTrap energyBot("EnergyTest");
  for (int i = 0; i < 101; i++) {
    energyBot.attack("Target");
  }
  energyBot.guardGate();

  std::cout << "\n--- End of Tests (destructors will be called) ---"
            << std::endl;
  return 0;
}
