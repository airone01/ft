#include "RPN.hpp"
#include <iostream>
#include <list>
#include <sys/types.h>

#define RPN_CHARS_DIGIT "0123456789"
#define RPN_CHARS_OP "+-*/"
#define RPN_CHARS " \t0123456789+-*/"

RPN::RPN() : _ops(std::list<t_ops>()), _digs(std::list<unsigned int>()) {}

RPN::~RPN() {}

RPN::RPN(const RPN &other) : _ops(other._ops), _digs(other._digs) {}

RPN RPN::operator=(const RPN &other) {
  if (this != &other) {
    _ops = other._ops;
    _digs = other._digs;
  }
  return *this;
}

/**
 * @brief counts each char of string s where char ∈ charset
 * @note using a bool table and casting chars to uint allows us to avoid having
 * to use a map
 */
ssize_t my_count(const std::string &s, const std::string &charset) {
  bool allowed[256] = {};
  for (std::string::size_type i = 0; i < charset.size(); i++)
    allowed[static_cast<unsigned int>(charset[i])] = true;
  ssize_t count = 0;
  for (std::string::size_type i = 0; i < s.size(); i++)
    if (allowed[static_cast<unsigned int>(s[i])])
      count++;
  return count;
}

/**
 * @throw IllegalCharacterException
 * @throw InvalidRpnException
 */
void RPN::parse(const std::string &s) {
  if (s.find_first_not_of(RPN_CHARS) != std::string::npos)
    throw IllegalCharacterException();

  std::string::difference_type digCount = my_count(s, RPN_CHARS_DIGIT);
  std::string::difference_type opCount = my_count(s, RPN_CHARS_OP);

  if ((opCount < 1) || (opCount != (digCount - 1)))
    throw InvalidRpnException();
}

const char *RPN::IllegalCharacterException::what() const throw() {
  return "illegal character in inverted Polish mathematical expression";
}

const char *RPN::InvalidRpnException::what() const throw() {
  return "invalid Polish mathematical expression";
}
