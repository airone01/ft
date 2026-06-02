
#ifndef _Brain_HPP_
#define _Brain_HPP_

#include <string>

class Brain {
public:
  Brain();
  Brain(Brain const &);
  ~Brain();

  Brain &operator=(const Brain &);

private:
  std::string _ideas[100];
};

#endif
