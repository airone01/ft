/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:51:00 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/12 10:13:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief This allows keeping track of what has been converted successfully
 */
typedef struct s_scalar_status {
  bool c;
  bool i;
  bool f;
  bool d;
} t_scalar_status;

/**
 * @brief Generic function to check if element is part of a vector
 * @note Templates are funny
 * @note I love TypeScript :-)
 */
template <typename T> bool is_any(const std::vector<T> &v, const T &x) {
  return (std::find(v.begin(), v.end(), x) != v.end());
}

/**
 * @brief Checks if s is a number keyword (i.e. "+inff") by leveraging is_any
 * with a vector.
 * @note I wish we had `{1, 2, 3}`, but we can't have nice things in C++ 98.
 */
bool is_number_keyword(const std::string &s) {
  std::vector<std::string> keywords;
  keywords.push_back("-inff");
  keywords.push_back("+inff");
  keywords.push_back("nanf");
  keywords.push_back("-inf");
  keywords.push_back("+inf");
  keywords.push_back("nan");

  return (is_any(keywords, s));
}

bool is_char(const std::string &s) {
  return s.length() == 1 && !isdigit(static_cast<char>(s[0]));
}

/**
 * @brief Reuse input string stream's error handling to check if string is a
 * valid number
 */
bool is_number(const std::string &s) {
  std::istringstream ss(s);
  double d;
  if (!(ss >> d))
    return false; // parse failed
  if (ss.eof())   // we're at eof, this is a clean double
    return true;
  char remaining;
  ss >> remaining;
  return (remaining == 'f' && ss.eof()); // char was f and the last char
}

/**
 * @brief Display all results
 */
void display_all(const t_scalar_status &st, const char &c, const int &i,
                 const float &f, const double &d) {
  std::string no_conv = "(impossible)";

  std::cout << "char:   ";
  if (st.c)
    if (std::isprint(c))
      std::cout << c << std::endl;
    else
      std::cout << "(non displayable)" << std::endl;
  else
    std::cout << no_conv << std::endl;
  std::cout << "int:    ";
  if (st.i)
    std::cout << i << std::endl;
  else
    std::cout << no_conv << std::endl;
  std::cout << "float:  ";
  if (st.f)
    std::cout << std::fixed << std::setprecision(1) << f << "f" << std::endl;
  else
    std::cout << no_conv << std::endl;
  std::cout << "double: ";
  if (st.d)
    std::cout << d << std::endl;
  else
    std::cout << no_conv << std::endl;
}

/**
 * @brief Disable displaying of all values
 * @note This is needed because `(type){.prop = val}` syntax does not work in
 * C++ 98, even if g++ with `-std=98` lets us compile. This can be proven by
 * passing the `-pedantic` flag to the C++ compiler.
 */
t_scalar_status reset_all_statuses(bool v) {
  t_scalar_status st;
  st.c = v;
  st.i = v;
  st.f = v;
  st.d = v;
  return (st);
}

/**
 * @brief Main convert static method
 */
void ScalarConverter::convert(const std::string &s) {
  t_scalar_status st = reset_all_statuses(true);
  char c = '0';
  int i = 0;
  float f = 0;
  double d = 0;

  if (is_char(s)) { // char
    c = s[0];
    i = static_cast<int>(c);
    f = static_cast<float>(c);
    d = static_cast<double>(c);
  } else if (is_number_keyword(s)) { // float/double
    try {
      d = std::atof(s.c_str());
      f = static_cast<float>(d);
      st.c = false;
      st.i = false;
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  } else if (is_number(s)) { // general number
    d = std::strtod(s.c_str(), NULL);
    // float's ::min() and ::max() are asymetrical. ::min() returns 0, hence
    // `-`.
    if (d >= -std::numeric_limits<float>::max() &&
        d <= std::numeric_limits<float>::max())
      f = static_cast<float>(d);
    else
      st.f = false;
    if (d >= std::numeric_limits<int>::min() &&
        d <= std::numeric_limits<int>::max())
      i = static_cast<int>(d);
    else
      st.i = false;
    if (d >= std::numeric_limits<char>::min() &&
        d <= std::numeric_limits<char>::max())
      c = static_cast<char>(d);
    else
      st.c = false;
  } else {
    st = reset_all_statuses(false);
  }

  display_all(st, c, i, f, d);
}
