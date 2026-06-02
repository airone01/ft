
#ifndef __HUMAN_B_HPP__
#define __HUMAN_B_HPP__

#include "Weapon.hpp"
#include <string>

class HumanB {

public:
  HumanB();
  HumanB(const HumanB &);
  HumanB(const std::string &name); // No weapon in constructor
  ~HumanB();

  HumanB &operator=(const HumanB &);

  void setWeapon(Weapon &);

  void attack();

private:
  std::string _name;
  Weapon *_weapon;
};

#endif // !__HUMAN_B_HPP__
