
#ifndef __CLAPTRAP_HPP__
#define __CLAPTRAP_HPP__

#include <string>
class ClapTrap {

public:
  ClapTrap();
  ClapTrap(const ClapTrap &);
  ~ClapTrap();

  ClapTrap(const std::string &name);

  ClapTrap &operator=(const ClapTrap &);

  void attack(const std::string &);
  void takeDamage(unsigned int);
  void beRepaired(unsigned int);

private:
  std::string _name;          // passed w/ constructor
  unsigned int _hitPoints;    // 10
  unsigned int _energyPoints; // 10
  unsigned int _attackDamage; // 0
};

#endif // !__CLAPTRAP_HPP__
