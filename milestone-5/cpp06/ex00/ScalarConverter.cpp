/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:51:00 by elagouch          #+#    #+#             */
/*   Updated: 2026/01/14 16:25:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

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
 * @brief Checks if s is a number keyword (i.e. "+inff") using standard arrays
 */
bool is_number_keyword(const std::string &s) {
  const std::string keywords[] = {"-inff", "+inff", "nanf",
                                  "-inf",  "+inf",  "nan"};
  const int count = 6;

  for (int i = 0; i < count; ++i) {
    if (s == keywords[i])
      return true;
  }
  return false;
}

bool is_char(const std::string &s) {
  return s.length() == 1 && !isdigit(static_cast<char>(s[0]));
}

/**
 * @brief Reuse input string stream's error handling to check if string is a
 * valid number
 */
bool is_number(const std::string &s) {
  if (s.empty())
    return false;

  char *endptr;
  std::strtod(s.c_str(), &endptr);
  // clean/double
  if (*endptr == '\0')
    return true;
  // float
  if (*endptr == 'f' && *(endptr + 1) == '\0')
    return true;
  return false;
}

/**
 * @brief Display all results
 */
void display_all(const t_scalar_status &st, const char &c, const int &i,
                 const float &f, const double &d) {
  std::string no_conv = "impossible";

  std::cout << "char:   ";
  if (st.c) {
    if (std::isprint(c))
      std::cout << "'" << c << "'" << std::endl;
    else
      std::cout << "Non displayable" << std::endl;
  } else {
    std::cout << no_conv << std::endl;
  }

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
    std::cout << std::fixed << std::setprecision(1) << d << std::endl;
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
  float f = 0.0f;
  double d = 0.0;

  if (is_char(s)) { // char
    c = s[0];
    i = static_cast<int>(c);
    f = static_cast<float>(c);
    d = static_cast<double>(c);
  } else if (is_number_keyword(s)) { // pseudo-literals
    d = std::atof(s.c_str());
    f = static_cast<float>(d);
    st.c = false;
    st.i = false;
  } else if (is_number(s)) { // general number
    d = std::strtod(s.c_str(), NULL);

    // note: numeric_limits<float>::max() is positive.
    if (d >= -std::numeric_limits<float>::max() &&
        d <= std::numeric_limits<float>::max())
      f = static_cast<float>(d);
    else if (std::isinf(d)) // Handle infinity from strtod
      f = static_cast<float>(d);
    else
      st.f = false;

    if (d >= static_cast<double>(std::numeric_limits<int>::min()) &&
        d <= static_cast<double>(std::numeric_limits<int>::max()))
      i = static_cast<int>(d);
    else
      st.i = false;

    if (d >= static_cast<double>(std::numeric_limits<char>::min()) &&
        d <= static_cast<double>(std::numeric_limits<char>::max()))
      c = static_cast<char>(d);
    else
      st.c = false;
  } else {
    st = reset_all_statuses(false);
  }

  display_all(st, c, i, f, d);
}
