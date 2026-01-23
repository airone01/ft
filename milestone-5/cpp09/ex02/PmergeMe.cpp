#include "PmergeMe.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <sched.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// this is sneaky
struct CompareIndices {
  const std::vector<unsigned long> &_data;

  CompareIndices(const std::vector<unsigned long> &data) : _data(data) {}

  bool operator()(size_t a, size_t b) const { return _data[a] < _data[b]; }
};

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

std::vector<size_t> sortIndices(std::vector<size_t> &indices,
                                std::vector<unsigned long> &data) {
  if (indices.size() < 2)
    return indices;

  // straggler handling
  bool hasStraggler = false;
  size_t stragglerIdx = 0;
  if (indices.size() % 2 == 1) {
    stragglerIdx = indices.back();
    indices.pop_back();
    hasStraggler = true;
  }

  // pairing
  std::vector<unsigned long> winners;
  std::vector<unsigned long> pairs(data.size() - 1);
  for (size_t i = 0; i + 1 < indices.size(); i += 2) {
    unsigned long idxA = indices[i];
    unsigned long idxB = indices[i + 1];

    if (data[idxA] > data[idxB]) {
      winners.push_back(idxA);
      pairs[idxA] = idxB; // instant link
    } else {
      winners.push_back(idxB);
      pairs[idxB] = idxA;
    }
  }

  // rec
  std::vector<size_t> sortedWinners = sortIndices(winners, data);

  // insertion
  std::vector<size_t> finalChain = sortedWinners;
  // immediatly insert first
  finalChain.insert(finalChain.begin(), pairs[sortedWinners[0]]);

  // jacobsthal loop
  size_t nPending = sortedWinners.size() - 1;
  std::vector<unsigned long> jacob = genJacobsthal(indices.size());
  size_t lastJacobIdx = 0;
  for (size_t i = 0; i < jacob.size(); i++) {
    size_t currentJacobIdx = jacob[i];
    if (currentJacobIdx >= nPending)
      currentJacobIdx = nPending - 1;

    // iterate backkwards from currentJacobIdx to lastJacobIdx
    for (size_t k = currentJacobIdx; k > lastJacobIdx; k--) {
      size_t winnerIdx = sortedWinners[k];
      size_t loserIdx = pairs[winnerIdx];

      // this might not be the fastest because we binary search the whole stack
      // instead of stopping early
      std::vector<unsigned long>::iterator pos = std::upper_bound(
          finalChain.begin(), finalChain.end(), loserIdx, CompareIndices(data));

      finalChain.insert(pos, loserIdx);
    }
    lastJacobIdx = currentJacobIdx;
  }

  // restore straggler
  if (hasStraggler) {
    std::vector<unsigned long>::iterator pos =
        std::upper_bound(finalChain.begin(), finalChain.end(), stragglerIdx);

    finalChain.insert(pos, stragglerIdx);
  }

  return finalChain;
}

void PmergeMe::sortVector() {
  std::vector<size_t> indices;
  for (size_t i = 0; i < _vec.size(); i++)
    indices.push_back(i);

  std::vector<size_t> sortedIndices = sortIndices(indices, _vec);

  std::vector<unsigned long> reconstructedData;
  for (size_t i = 0; i < sortedIndices.size(); i++)
    reconstructedData.push_back(_vec[sortedIndices[i]]);
}

const char *PmergeMe::InvalidInputException::what() const throw() {
  return "invalid input";
}
