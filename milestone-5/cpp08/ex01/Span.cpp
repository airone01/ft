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
    this->_max = other._max;
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

  for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end() - 1; it++) {
    long dist = std::abs(static_cast<long>(*(it + 1)) - static_cast<long>(*it));
    if (dist == 0)
      return 0;
    if (dist < sd)
      sd = static_cast<int>(dist);
  }

  return sd;
}

/**
 * @note usage of stl's algos to find shortest span
 */
int Span::longestSpan() const {
  if (_elems.size() <= 1)
    throw std::out_of_range("not enough elements to calculate a Span");

  std::vector<int>::const_iterator min_it =
      std::min_element(_elems.begin(), _elems.end());
  std::vector<int>::const_iterator max_it =
      std::max_element(_elems.begin(), _elems.end());

  return static_cast<int>(static_cast<long>(*max_it) -
                          static_cast<long>(*min_it));
}
