/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:50:42 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/05 13:38:03 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <exception>
#include <ostream>
#include <string>

#ifndef __AFORM_HPP__
#define __AFORM_HPP__

class AForm {
public:
  // canonical
  AForm();
  AForm(const AForm &);
  virtual ~AForm();
  AForm &operator=(const AForm &);

  AForm(std::string name, int minSigningGrade, int minExecutionGrade);

  std::string getName() const;
  bool isSigned() const;
  int getMinSigningGrade() const;
  int getMinExecutionGrade() const;

  void beSigned(Bureaucrat &);

  // pure virt func makes class abstract
  virtual void execute(Bureaucrat const &executor) const = 0;

  // exceptions
  class GradeTooHighException : public std::exception {
  public:
    virtual const char *what() const throw();
  };
  class GradeTooLowException : public std::exception {
  public:
    virtual const char *what() const throw();
  };
  class FormNotSignedException : public std::exception {
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
std::ostream &operator<<(std::ostream &os, const AForm &);

#endif // !__AFORM_HPP__
