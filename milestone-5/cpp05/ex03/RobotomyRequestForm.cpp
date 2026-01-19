#include "RobotomyRequestForm.hpp"
#include <cstdlib>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm()
    : AForm("Robotomy Request Form", 72, 45), _target("default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
    : AForm("Robotomy Request Form", 72, 45), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
    : AForm(other), _target(other._target) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm &
RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
  if (this != &other) {
    AForm::operator=(other);
    _target = other._target;
  }
  return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
  if (!this->isSigned())
    throw AForm::FormNotSignedException();
  if (executor.getGrade() > this->getMinExecutionGrade())
    throw AForm::GradeTooLowException();

  std::cout << "* DRRRRRR... VREEEEEE... KRK KRK... *" << std::endl;
  if (std::rand() % 2)
    std::cout << _target << " has been robotomized successfully!" << std::endl;
  else
    std::cout << "Robotomy on " << _target << " failed." << std::endl;
}
