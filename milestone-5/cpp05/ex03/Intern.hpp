/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:34:48 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/05 13:35:44 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
