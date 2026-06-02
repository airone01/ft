
#ifndef __AANIMAL_HPP__
#define __AANIMAL_HPP__

#include <string>

class AAnimal {

public:
  AAnimal(void);
  AAnimal(const std::string &);
  AAnimal(const AAnimal &);
  virtual ~AAnimal(void);

  AAnimal &operator=(const AAnimal &);

  const std::string getType(void) const;

  // This is a pure-virtual method, making the class abstract
  // So now, we can't instanciate it :-)
  virtual void makeSound(void) const = 0;

protected:
  std::string _type;
};

#endif // !__AANIMAL_HPP__
