
#ifndef __WRONGANIMAL_HPP__
#define __WRONGANIMAL_HPP__

#include <string>

class WrongAnimal {
public:
  WrongAnimal();
  WrongAnimal(const std::string &);
  WrongAnimal(const WrongAnimal &);
  ~WrongAnimal(); // not virtual

  WrongAnimal &operator=(const WrongAnimal &obj);

  const std::string getType(void) const;

  void makeSound(void) const; // not virtual

protected:
  std::string _type;
};

#endif // !__WRONGANIMAL_HPP__
