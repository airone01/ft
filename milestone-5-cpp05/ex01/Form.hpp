/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:50:42 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/05 10:14:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

  Form(std::string name, const int minSigningGrade, int minExecutionGrade);

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
