#include "Bureaucrat.hpp"
#include <exception>
#include <ostream>
#include <string>

#ifndef __FORM_HPP__
#define __FORM_HPP__

class Form {
public:
  // canonical
  Form();
  Form(const Form &);
  ~Form();
  Form &operator=(const Form &);

  Form(std::string name, int minSigningGrade, int minExecutionGrade);

  std::string getName() const;
  bool isSigned() const;
  int getMinSigningGrade() const;
  int getMinExecutionGrade() const;

  void beSigned(Bureaucrat &);

  // exceptions
  class GradeTooHighException : public std::exception {
  public:
    virtual const char *what() const throw();
  };
  class GradeTooLowException : public std::exception {
  public:
    virtual const char *what() const throw();
  };

private:
  const std::string _name;
  bool _signed;
  const int _minSigningGrade;
  const int _minExecutionGrade;
};

// ostream overload
std::ostream &operator<<(std::ostream &os, const Form &);

#endif // !__FORM_HPP__
