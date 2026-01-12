/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:27:00 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/12 17:35:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <cstring>
#include <iostream>
#include <ostream>

// The magic table™
const Harl::LevelEntry Harl::levels[] = {
    {"DEBUG", &Harl::debug},
    {"INFO", &Harl::info},
    {"WARNING", &Harl::warning},
    {"ERROR", &Harl::error},
};

// Default constructor
Harl::Harl() {}
// // Copy constructor
// Harl::Harl(const Harl &other) {};

// Destructor
Harl::~Harl() {}

// // Copy asignment operator
// Harl &Harl::operator=(const Harl &other) { return *this; };

// Methods
void Harl::complain(std::string level) {
  for (int i = 0; i < levelsCount; i++) {
    if (level == levels[i].level) {
      (this->*(levels[i].function))();
      return ;
    }
  }
  std::cout << "Err: Unknown log level." << std::endl;
}
void Harl::debug(void) {
  std::cout
      << "[DBUG] I love having extra bacon for my "
         "7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!"
      << std::endl;
}
void Harl::info(void) {
  std::cout
      << "[INFO] I cannot believe adding extra bacon costs more money. You didn’t put "
         "enough bacon in my burger! If you did, I wouldn’t be asking for more!"
      << std::endl;
}
void Harl::warning(void) {
  std::cout
      << "[WARN] I think I deserve to have some extra bacon for free. I’ve been "
         "coming for years whereas you started working here since last month."
      << std::endl;
}
void Harl::error(void) {
  std::cout << "[ERR ] This is unacceptable! I want to speak to the manager now."
            << std::endl;
}
