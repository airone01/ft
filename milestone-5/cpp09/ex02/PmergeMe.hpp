#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sched.h>
#include <sstream>
#include <string>

/**
 * @tparam _C container type, defaults to `std::vector`
 */
template <class _C> class PmergeMe {
public:
  // OCF
  PmergeMe() : _data(_C()) {}
  PmergeMe(const PmergeMe &o) : _data(o._data) {}
  PmergeMe operator=(const PmergeMe &o) {
    if (this != &o)
      _data = o._data;
    return *this;
  }
  ~PmergeMe() {}

  PmergeMe(_C &data) : _data(data) {}

  PmergeMe(const std::string &str) : _data(_C()) {
    if (str.empty() ||
        (str.find_first_not_of(" \t0123456789") != std::string::npos))
      throw InvalidInputException();

    std::istringstream iss(str);
    unsigned long n;
    while (iss >> n)
      _data.push_back(n);
  }

  void sort() {
    _C indices;
    for (size_t i = 0; i < _data.size(); i++)
      indices.push_back(i);
    _C sortedIndices = sortIndices(indices, _data);
    _C reconstructedData;
    for (size_t i = 0; i < sortedIndices.size(); i++)
      reconstructedData.push_back(_data[sortedIndices[i]]);
    _data = reconstructedData;
  }

  const _C &getData() const { return _data; }

  class InvalidInputException : public std::exception {
    virtual const char *what() const throw() { return "invalid input"; };
  };

private:
  _C _data;

  struct CompareIndices {
    const _C &_data;
    CompareIndices(const _C &data) : _data(data) {}
    bool operator()(size_t a, size_t b) const { return _data[a] < _data[b]; }
  };

  _C sortIndices(_C &indices, _C &data) {
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
    _C winners;
    _C pairs(data.size());
    for (size_t i = 0; i + 1 < indices.size(); i += 2) {
      ulong idxA = indices[i];
      ulong idxB = indices[i + 1];

      if (data[idxA] > data[idxB]) {
        winners.push_back(idxA);
        pairs[idxA] = idxB; // instant link
      } else {
        winners.push_back(idxB);
        pairs[idxB] = idxA;
      }
    }

    // rec
    _C sortedWinners = sortIndices(winners, data);

    // insertion
    _C finalChain = sortedWinners;
    // immediatly insert first
    finalChain.insert(finalChain.begin(), pairs[sortedWinners[0]]);

    // jacobsthal loop
    size_t nPending = sortedWinners.size() - 1;
    _C jacob = genJacobsthal(indices.size());
    size_t lastJacobIdx = 0;
    for (size_t i = 0; i < jacob.size(); i++) {
      size_t currentJacobIdx = jacob[i];
      if (currentJacobIdx >= nPending)
        currentJacobIdx = nPending;

      // iterate backkwards from currentJacobIdx to lastJacobIdx
      for (size_t k = currentJacobIdx; k > lastJacobIdx; k--) {
        size_t winnerIdx = sortedWinners[k];
        size_t loserIdx = pairs[winnerIdx];

        // this might not be the fastest because we binary search the whole
        // stack instead of stopping early
        typename _C::iterator pos =
            std::upper_bound(finalChain.begin(), finalChain.end(), loserIdx,
                             CompareIndices(data));

        finalChain.insert(pos, loserIdx);
      }
      lastJacobIdx = currentJacobIdx;
    }

    // restore straggler
    if (hasStraggler) {
      typename _C::iterator pos =
          std::upper_bound(finalChain.begin(), finalChain.end(), stragglerIdx,
                           CompareIndices(data));
      finalChain.insert(pos, stragglerIdx);
    }

    return finalChain;
  }

  /**
   * @note a(n) = a(n-1) + 2*a(n-2), with a(0) = 0, a(1) = 1; also a(n) =
   * nearest integer to 2^n/3
   * @todo optimize
   *
   * @see https://oeis.org/A001045
   * @see https://en.wikipedia.org/wiki/Jacobsthal_number
   */
  _C genJacobsthal(size_t len) {
    _C j;
    if (len > 0)
      j.push_back(0);
    if (len > 1)
      j.push_back(1);
    ulong pprev = 0;
    ulong prev = 1;
    for (ulong n = 2; n < len; n++) {
      ulong tmp = prev + 2 * pprev;
      j.push_back(tmp);
      pprev = prev;
      prev = tmp;
    }
    return j;
  }
};

/**
 * @brief formats a container for an ostream
 * @note this exists because `fmt` and other solutions don't exist in 98
 * @note tested with `std::vector` and `std::deque`
 */
template <template <typename, typename> class _C, typename _A>
std::ostream &operator<<(std::ostream &os, const _C<unsigned long, _A> &c) {
  typename _C<unsigned long, _A>::const_iterator it = c.begin();
  os << "[";
  while (it != c.end()) {
    os << *it;
    if (++it != c.end())
      os << ",";
  }
  os << "]";
  return os;
}

#endif // !PMERGEME_HPP
