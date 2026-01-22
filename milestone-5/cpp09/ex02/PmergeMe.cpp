#include "PmergeMe.hpp"
#include <algorithm>
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

/**
 * @note a(n) = a(n-1) + 2*a(n-2), with a(0) = 0, a(1) = 1; also a(n) = nearest
 * integer to 2^n/3
 * @TODO optimize
 *
 * @see https://oeis.org/A001045
 * @see https://en.wikipedia.org/wiki/Jacobsthal_number
 */
std::vector<unsigned long> genJacobsthal(unsigned long len) {
  std::vector<unsigned long> j;
  if (len > 0)
    j.push_back(0);
  if (len > 1)
    j.push_back(1);
  unsigned long pprev = 0;
  unsigned long prev = 1;
  for (unsigned long n = 2; n < len; n++) {
    unsigned long tmp = prev + 2 * pprev;
    j.push_back(tmp);
    pprev = prev;
    prev = tmp;
  }
  return j;
}

bool binarySearch(std::vector<unsigned long> &v, unsigned long target) {
  unsigned long low = 0, high = v.size() - 1;
  // loop until element found or vec can'  be devided anymore
  while (low <= high) {
    unsigned long mid = ((high - low) / 2) + low; // find mid point
    if (v[mid] == target)
      return true;
    if (v[mid] > target) // if greater, search left half
      high = mid - 1;
    else // otherwise earch right half
      low = mid + 1;
  }
  return false;
}

// in pairs each pair has lower number first, bigger last
typedef std::pair<unsigned long, unsigned long> myPair;

std::vector<unsigned long> sortVector(std::vector<unsigned long> vec) {
  if (vec.size() < 2)
    return vec;

  bool hasStraggler = false;
  unsigned long straggler = 0;
  if (vec.size() % 2 == 1) {
    straggler = vec.back();
    vec.pop_back();
    hasStraggler = true;
  }

  std::vector<myPair> pairs;
  for (unsigned long i = 0; i + 1 < vec.size(); i += 2) {
    unsigned long low = vec[i];
    unsigned long large = vec[i + 1];
    if (low > large)
      std::swap(low, large);
    pairs.push_back(myPair(low, large));
  }

  // extract the large
  std::vector<unsigned long> chain;
  std::vector<myPair>::iterator pIt = pairs.begin();
  for (; pIt < pairs.end(); pIt++)
    chain.push_back(pIt->second);

  chain = sortVector(chain); // rec

  // need to know which small value belonged to which large
  std::vector<unsigned long> pending;
  std::vector<unsigned long>::iterator mIt = chain.begin();
  for (; mIt < chain.end(); mIt++) {
    pIt = pairs.begin();
    for (bool cont = true; cont && pIt < pairs.end(); pIt++)
      if (pIt->second == *mIt) {
        pending.push_back(pIt->first);
        cont = false;
      }
  }

  // now the binary insert
  std::vector<unsigned long> partners = chain;
  // immediatly insert first loser
  chain.insert(chain.begin(), pending[0]);
  std::vector<unsigned long> jacob = genJacobsthal(vec.size());

  unsigned long lastJacobIdx = 0;
  for (size_t i = 0; i < jacob.size(); i++) {
    size_t currentJacobIdx = jacob[i];
    if (currentJacobIdx >= pending.size())
      currentJacobIdx = pending.size() - 1;
    // iterate backkwards from currentJacobIdx to lastJacobIdx
    for (size_t k = currentJacobIdx; k > lastJacobIdx; k--) {
      unsigned long loser = pending[k];
      unsigned long partnerVal = partners[k];
      std::vector<unsigned long>::iterator partnerIt =
        std::find(chain.begin(), chain.end(), partnerVal);
      std::vector<unsigned long>::iterator pos =
        std::upper_bound(chain.begin(), partnerIt, loser);
      chain.insert(pos, loser);
    }
    lastJacobIdx = currentJacobIdx;
  }

  // restore straggler
  if (hasStraggler) {
    std::vector<unsigned long>::iterator pos =
        std::upper_bound(chain.begin(), chain.end(), straggler);
    chain.insert(pos, straggler);
  }

  return chain;
}

void PmergeMe::sortVector() {
  _vec = ::sortVector(_vec);
}

const char *PmergeMe::InvalidInputException::what() const throw() {
  return "invalid input";
}
