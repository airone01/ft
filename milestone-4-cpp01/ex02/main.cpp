/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:01:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/21 17:17:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <iostream>
#include <string>

int main(void) {
  std::string str = "HI THIS IS BRAINZ";
  std::string *stringPTR = &str;
  std::string &stringREF = str;

  std::cout << "Memory address of the string variable: " << &str << std::endl
            << std::setw(39)
            << "Memory address held by stringPTR: " << stringPTR << std::endl
            << std::setw(39)
            << "Memory address held by stringREF: " << &stringREF << std::endl
            << std::endl;
  std::cout << std::setw(31) << "Value of the string variable: " << str
            << std::endl
            << std::setw(31) << "Value pointed to by stringPTR: " << *stringPTR
            << std::endl
            << std::setw(31) << "Value pointed to by stringREF: " << stringREF
            << std::endl;
}
