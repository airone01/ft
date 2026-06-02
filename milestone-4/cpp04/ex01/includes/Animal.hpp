
#ifndef __ANIMAL_HPP__
#define __ANIMAL_HPP__

#include <string>

class Animal {

public:
  Animal(void);
  Animal(const std::string &);
  Animal(const Animal &);
  virtual ~Animal(void);

  Animal &operator=(const Animal &);

  const std::string getType(void) const;

  virtual void makeSound(void) const;

protected:
  std::string _type;
};

#endif // !__ANIMAL_HPP__
