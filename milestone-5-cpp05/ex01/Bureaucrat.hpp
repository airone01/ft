/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:15:44 by elagouch          #+#    #+#             */
/*   Updated: 2025/12/29 12:38:51 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <string>

#ifndef __BUREAUCRAT_HPP__
#define __BUREAUCRAT_HPP__

class Form;

class Bureaucrat {
public:
  // canonical
  Bureaucrat();
  Bureaucrat(const Bureaucrat &);
  ~Bureaucrat();
  Bureaucrat &operator=(const Bureaucrat &);

  // parameterized constructors
  Bureaucrat(const std::string name, int grade);

  // getters
  const std::string getName(void) const;
  int getGrade(void) const;

  // setters
  void incrementGrade(void);
  void decrementGrade(void);
  void signForm(Form &fm);

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
  int _grade;
};

// ostream overload
std::ostream &operator<<(std::ostream &os, const Bureaucrat &);

#endif // !__BUREAUCRAT_HPP__
