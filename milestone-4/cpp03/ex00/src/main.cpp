
#include "ClapTrap.hpp"
#include <iostream>
#include <ostream>

int main() {
  std::cout << "=== ClapTrap Tests ===" << std::endl;

  std::cout << "\n--- Default Constructor ---" << std::endl;
  ClapTrap defaultBot;

  std::cout << "\n--- Named Constructor ---" << std::endl;
  ClapTrap namedBot("Destroyer");

  std::cout << "\n--- Copy Constructor ---" << std::endl;
  ClapTrap copiedBot(namedBot);

  std::cout << "\n--- Basic Actions ---" << std::endl;
  namedBot.attack("Enemy");
  namedBot.takeDamage(30);
  namedBot.beRepaired(15);

  std::cout << "\n--- Energy Test ---" << std::endl;
  ClapTrap energyBot("EnergyTest");
  for (int i = 0; i < 101; i++) {
    energyBot.attack("Target");
  }

  std::cout << "\n--- End of Tests (destructors will be called) ---"
            << std::endl;
  return 0;
}
