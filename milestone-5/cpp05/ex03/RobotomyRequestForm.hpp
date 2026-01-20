#ifndef __ROBOTOMYREQUESTFORM_HPP__
#define __ROBOTOMYREQUESTFORM_HPP__

#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
public:
  RobotomyRequestForm();
  RobotomyRequestForm(const std::string &target);
  RobotomyRequestForm(const RobotomyRequestForm &other);
  ~RobotomyRequestForm();
  RobotomyRequestForm &operator=(const RobotomyRequestForm &other);

  void execute(Bureaucrat const &executor) const;

private:
  std::string _target;
};

#endif // !__ROBOTOMYREQUESTFORM_HPP__
