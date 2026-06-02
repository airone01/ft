
#include "Zombie.hpp"

int main(void) {
  int N = 7;
  Zombie *zombs = zombieHorde(N, "Ed");
  for (int i = 0; i < N; i++) {
    zombs[i].announce();
  }
  delete[] zombs;
}
