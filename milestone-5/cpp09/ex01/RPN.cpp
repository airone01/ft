#include "RPN.hpp"
#include <list>

RPN::RPN() : _ops(std::list<t_ops>()), _nbrs(std::list<unsigned int>()) {}

RPN::~RPN() {}

RPN::RPN(const RPN &other) : _ops(other._ops), _nbrs(other._nbrs) {}

RPN RPN::operator=(const RPN &other) {
  if (this != &other) {
    _ops = other._ops;
    _nbrs = other._nbrs;
  }
  return *this;
}
