#ifndef __PRESIDENTIALPARDONFORM_HPP__
#define __PRESIDENTIALPARDONFORM_HPP__

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
public:
  PresidentialPardonForm();
  PresidentialPardonForm(const std::string &target);
  PresidentialPardonForm(const PresidentialPardonForm &other);
  ~PresidentialPardonForm();
  PresidentialPardonForm &operator=(const PresidentialPardonForm &other);

  void execute(Bureaucrat const &executor) const;

private:
  std::string _target;
};

#endif // !__PRESIDENTIALPARDONFORM_HPP__
