#include "Span.hpp"
#include <stdexcept>
#include <vector>

Span::Span(unsigned int max) : _max(max), _elems(std::vector<int>()) {}

void Span::addNumber(int n) {
  if (_elems.size() == _max)
    throw std::out_of_range("array is full!");
  _elems.push_back(n);
}

int distance(int x, int y) {
  int d = (y - x) & 7;
  return d > 4 ? d - 8 : d;
}

int Span::shortestSpan() const {
  int sp = // int max

  for (int i = 0; i < _elems.size(); i++) {
    for (int j = 0; j < _elems.size(); j++) {
       // distamce();
    }
  }

  throw std::out_of_range("not enough elements to calculate a Span");
}
