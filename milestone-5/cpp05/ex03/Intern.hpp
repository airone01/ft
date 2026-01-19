#ifndef __INTERN_HPP__
#define __INTERN_HPP__

#include "AForm.hpp"
#include <string>

class Intern {
public:
  Intern();
  Intern(const Intern &other);
  ~Intern();
  Intern &operator=(const Intern &other);

  AForm *makeForm(std::string formName, std::string target);
};

#endif // !__INTERN_HPP__
