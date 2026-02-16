#include "RPN.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stack>

#define RPN_CHARS_DIGIT "0123456789"
#define RPN_CHARS_OP "+-*/"
#define RPN_CHARS " \t0123456789+-*/"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &) {}

RPN RPN::operator=(const RPN &) { return *this; }

/**
 * @brief counts each char of string s where char ∈ charset
 * @note using a bool table and casting chars to uint allows us to avoid having
 * to use a map
 */
long my_count(const std::string &s, const std::string &charset) {
  bool allowed[256] = {};
  for (std::string::size_type i = 0; i < charset.size(); i++)
    allowed[static_cast<unsigned int>(charset[i])] = true;
  long count = 0;
  for (std::string::size_type i = 0; i < s.size(); i++)
    if (allowed[static_cast<unsigned int>(s[i])])
      count++;
  return count;
}

/**
 * @brief handles boring safe calculation and error-proning
 */
static void _handleCalcs(std::stack<long> &st, char c) {
  long x = st.top();
  st.pop();
  long y = st.top();
  st.pop();

  switch (c) {
  case ADD:
    if (x > 0 && (y > std::numeric_limits<long>::max() - x))
      throw RPN::OverflowException();
    if (x < 0 && (y < std::numeric_limits<long>::min() - x))
      throw RPN::OverflowException();
    st.push(y + x);
    break;
  case SUB:
    if (x < 0 && (y > std::numeric_limits<long>::max() + x))
      throw RPN::OverflowException();
    if (x > 0 && (y < std::numeric_limits<long>::min() + x))
      throw RPN::OverflowException();
    st.push(y - x);
    break;
  case MULT:
    if (x == 0 || y == 0) {
      st.push(0);
      break;
    }
    if (x > 0 && y > 0) { // both pos
      if (y > std::numeric_limits<long>::max() / x)
        throw RPN::OverflowException();
    } else if (x < 0 && y < 0) { // both neg, result pos, check against max
      if (y < std::numeric_limits<long>::max() / x)
        throw RPN::OverflowException();
    } else {       // mixed pos/neg, result neg, check against min
      if (x > 0) { // x pos y neg
        if (y < std::numeric_limits<long>::min() / x)
          throw RPN::OverflowException();
      } else { // x neg y pos
        if (y > std::numeric_limits<long>::min() / x)
          throw RPN::OverflowException();
      }
    }
    st.push(y * x);
    break;
  case DIV:
    if (!x)
      throw RPN::DivByZeroException();
    st.push(y / x);
    break;
  }
}

/**
 * @throw IllegalCharacterException
 * @throw InvalidRpnException
 *
 * @note we're using std::stack<long> because stacks are FILO, which is what
 * we're looking for exactly
 *
 * @ref
 * https://rosettacode.org/wiki/Parsing/RPN_calculator_algorithm?oldid=393241#Version_2
 */
void RPN::parse(const std::string &str) {
  if (str.find_first_not_of(RPN_CHARS) != std::string::npos)
    throw IllegalCharacterException();

  std::string::difference_type digCount = my_count(str, RPN_CHARS_DIGIT);
  std::string::difference_type opCount = my_count(str, RPN_CHARS_OP);
  if ((opCount == 0 && digCount != 1) || (opCount != (digCount - 1)))
    throw InvalidRpnException();

  std::stack<long> st;
  std::string newStr = str;
  for (std::string::iterator it = newStr.begin(); it < newStr.end(); it++) {
    std::string smStr(1, *it);
    if (std::string(" \t").find_first_of(smStr) != std::string::npos)
      continue;
    if (std::string(RPN_CHARS_OP).find_first_of(smStr) == std::string::npos) {
      st.push(static_cast<long>(*it - '0'));
      continue;
    }
    if (st.size() < 2)
      throw InvalidRpnException();
    _handleCalcs(st, *it);
  }

  if (st.size() != 1)
    throw InvalidRpnException();

  std::cout << st.top() << std::endl;
}

const char *RPN::IllegalCharacterException::what() const throw() {
  return "illegal character in inverted polish mathematical expression";
}

const char *RPN::InvalidRpnException::what() const throw() {
  return "invalid inverted polish mathematical expression";
}

const char *RPN::DivByZeroException::what() const throw() {
  return "attempted to divide by zero";
}

const char *RPN::OverflowException::what() const throw() {
  return "the expression would over/underflow";
}
