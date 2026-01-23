#include "PmergeMe.hpp"
#include <cstdlib>
#include <deque>
#include <iostream>
#include <sched.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

PmergeMe::PmergeMe()
    : _vec(std::vector<unsigned long>()), _deq(std::deque<unsigned long>()) {}

PmergeMe::PmergeMe(const PmergeMe &other)
    : _vec(other._vec), _deq(other._deq) {}

PmergeMe PmergeMe::operator=(const PmergeMe &other) {
  if (this != &other) {
    _vec = other._vec;
    _deq = other._deq;
  }
  return *this;
}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const std::string &s)
    : _vec(std::vector<unsigned long>()), _deq(std::deque<unsigned long>()) {
  if (s.empty() || (s.find_first_not_of(" \t0123456789") != std::string::npos))
    throw InvalidInputException();

  std::istringstream iss(s);
  unsigned long n;
  while (iss >> n) {
    _vec.push_back(n);
    _deq.push_back(n);
  }
}

const std::vector<unsigned long> &PmergeMe::getVector() const { return _vec; }

const std::deque<unsigned long> &PmergeMe::getDeque() const { return _deq; }

void PmergeMe::sortVector() {
  sort<std::vector>(_vec);
}

void PmergeMe::sortDeque() {
  sort(_deq);
}

// in pairs each pair has lower number first, bigger last
typedef std::pair<unsigned long, unsigned long> myPair;

const char *PmergeMe::InvalidInputException::what() const throw() {
  return "invalid input";
}
