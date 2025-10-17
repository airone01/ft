/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:25:09 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/25 13:58:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HARL_HPP__
#define __HARL_HPP__

#include <string>

class Harl {

public:
  Harl();
  // Harl(const Harl &);
  ~Harl();

  // Harl &operator=(const Harl &);

  void complain(std::string level);

private:
  void debug(void);
  void info(void);
  void warning(void);
  void error(void);

  typedef void (Harl::*HarlFunction)(void);
  struct LevelEntry {
    std::string level;
    HarlFunction function;
  };
  static const LevelEntry levels[];
  static const int levelsCount = 4;
};

#endif // !__HARL_HPP__
