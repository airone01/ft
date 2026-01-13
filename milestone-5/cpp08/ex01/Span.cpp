#include "Span.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

Span::Span(unsigned int max) : _max(max), _elems(std::vector<int>()) {}

Span::~Span() {}

Span::Span(const Span &other)
    : _max(other._max), _elems(other._elems) {} // std::vector can handle itself

Span &Span::operator=(const Span &other) {
  if (this != &other) {
    this->_elems = other._elems; // std::vector can handle itself
  }
  return *this;
}

void Span::addNumber(int n) {
  if (_elems.size() == _max)
    throw std::out_of_range("array is full!");
  _elems.push_back(n);
}

/**
 * @note optimized by pre-sorting and then checking the distance between
 * neighbors
 */
int Span::shortestSpan() const {
  int sd = std::numeric_limits<int>::max();

  if (_elems.size() <= 1)
    throw std::out_of_range("not enough elements to calculate a Span");

  std::vector<int> tmp = _elems;
  std::sort(tmp.begin(), tmp.end());

  unsigned long sz = tmp.size();
  for (unsigned int i = 0; i < tmp.size(); i++) {
    if (sz <= i + 1)
      continue;
    int dst = std::abs(tmp[i] - tmp[i + 1]);
    if (dst == 0)
      return 0;
    if (dst < sd)
      sd = dst;
  }

  return sd;
}

int Span::longestSpan() const {
  int small = std::numeric_limits<int>::max();
  int big = std::numeric_limits<int>::min();

  if (_elems.size() <= 1)
    throw std::out_of_range("not enough elements to calculate a Span");

  for (unsigned int i = 0; i < _elems.size(); i++) {
    if (_elems[i] > big)
      big = _elems[i];
    if (_elems[i] < small)
      small = _elems[i];
  }

  return std::abs(small - big);
}

// void Span::populate(unsigned int end, int (*f)(unsigned int i)) {
//   for (unsigned int i = 0; i < end; i++)
//     if (_elems.size() <= i)
//       _elems.push_back(f(i));
//     else
//       _elems[i] = f(i);
// }
