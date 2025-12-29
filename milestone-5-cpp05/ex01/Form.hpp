/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:50:42 by elagouch          #+#    #+#             */
/*   Updated: 2025/12/29 12:21:45 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FORM_HPP__
#define __FORM_HPP__

#include "Bureaucrat.hpp"
#include <exception>
#include <ostream>

class Form {
public:
  // canonical
  Form();
  Form(const Form &);
  ~Form();
  Form &operator=(const Form &);

  Form(const int minSigningGrade, int minExecutionGrade);

  bool isSigned() const;
  int getMinSigningGrade() const;
  int getMinExecutionGrade() const;

  void beSigned(const Bureaucrat &);
  void signForm(const Bureaucrat &bc);

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
  bool _signed;
  const int _minSigningGrade;
  const int _minExecutionGrade;
};

// ostream overload
std::ostream &operator<<(std::ostream &os, const Form &);

#endif // !__FORM_HPP__
