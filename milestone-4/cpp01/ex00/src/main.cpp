
#include "Zombie.hpp"

int main() {
  randomChump("Gedagedigedagedago");
  Zombie *zomb = newZombie("Gedagedigedagedago2");
  zomb->announce();
  delete zomb;
}
