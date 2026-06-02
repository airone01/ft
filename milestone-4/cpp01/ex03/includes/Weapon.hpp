
#ifndef __WEAPON_HPP__
#define __WEAPON_HPP__

#include <string>

class Weapon {
public:
  Weapon();
  Weapon(const Weapon &);
  Weapon(const std::string &nType);
  ~Weapon();

  std::string &getType();
  void setType(const std::string &newType);

private:
  std::string _type;
};

#endif // !__WEAPON_HPP__
