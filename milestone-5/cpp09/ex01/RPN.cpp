#include "RPN.hpp"
#include <cstdlib>
#include <iostream>
#include <stack>
#include <sys/types.h>

#define RPN_CHARS_DIGIT "0123456789"
#define RPN_CHARS_OP "+-*/"
#define RPN_CHARS " \t0123456789+-*/"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &) {
}

RPN RPN::operator=(const RPN &) {
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

template <class T> T add(T x, T y) { return y + x; }
template <class T> T sub(T x, T y) { return y - x; }
template <class T> T mult(T x, T y) { return y * x; }
template <class T> T div(T x, T y) { return y / x; }
typedef long (*aFunc)(long, long);
typedef aFunc Dispatcher[50];

/**
 * @throw IllegalCharacterException
 * @throw InvalidRpnException
 *
 * @note we're using std::stack<long> because stacks are FILO, which is what
 * we're looking for exactly
 */
void RPN::parse(const std::string &str) {
  if (str.find_first_not_of(RPN_CHARS) != std::string::npos)
    throw IllegalCharacterException();

  std::string::difference_type digCount = my_count(str, RPN_CHARS_DIGIT);
  std::string::difference_type opCount = my_count(str, RPN_CHARS_OP);
  if ((opCount < 1) || (opCount != (digCount - 1)))
    throw InvalidRpnException();

  Dispatcher d;
  d[static_cast<size_t>(ADD)] = &add;
  d[static_cast<size_t>(SUB)] = &sub;
  d[static_cast<size_t>(MULT)] = &mult;
  d[static_cast<size_t>(DIV)] = &div;

  std::stack<long> st;
  std::string newStr = str;
  for (std::string::iterator it = newStr.begin(); it < newStr.end(); it++) {
    std::string smStr(1, *it);
    if (std::string(" \t").find_first_of(smStr) != std::string::npos)
      continue;
    if (std::string(RPN_CHARS_OP).find_first_of(smStr) != std::string::npos) {
      long x = st.top();
      st.pop();
      long y = st.top();
      st.pop();
      st.push(d[static_cast<size_t>(*it)](x, y));
    } else
      st.push(static_cast<long>(*it - '0'));
  }

  std::cerr << st.top() << std::endl;
}

const char *RPN::IllegalCharacterException::what() const throw() {
  return "illegal character in inverted Polish mathematical expression";
}

const char *RPN::InvalidRpnException::what() const throw() {
  return "invalid Polish mathematical expression";
}
