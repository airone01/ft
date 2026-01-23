#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sched.h>
#include <sstream>
#include <string>
#include <vector>

/**
 * @tparam _C container type
 * @tparam _A STD allocator
 */
template <template <class, class> class _C, class _A> class PmergeMe {
public:
  // OCF
  PmergeMe() : _data(_C<unsigned long, _A>()) {}
  PmergeMe(const PmergeMe &o) : _data(o._data) {}
  PmergeMe operator=(const PmergeMe &o) {
    if (this != &o)
      _data = o._data;
    return *this;
  }
  ~PmergeMe() {}

  PmergeMe(_C<unsigned long, _A> &data) : _data(data) {}

  PmergeMe(const std::string &str) : _data(_C<unsigned long, _A>()) {
    if (str.empty() ||
        (str.find_first_not_of(" \t0123456789") != std::string::npos))
      throw InvalidInputException();

    std::istringstream iss(str);
    unsigned long n;
    while (iss >> n)
      _data.push_back(n);
  }

  /* cannot forward CData def here, hence why writing all the types manually */

  const std::vector<ulong> &getData() const { return _data; }

  class InvalidInputException : public std::exception {
    virtual const char *what() const throw() { return "invalid input"; };
  };

private:
  typedef _C<unsigned long, _A> CData;
  typedef _C<size_t, _A> CIndice;

  CData _data;

  struct CompareIndices {
    const CData &_data;
    CompareIndices(const CData &data) : _data(data) {}
    bool operator()(size_t a, size_t b) const { return _data[a] < _data[b]; }
  };

  CIndice sortIndices(CIndice &indices, CData &data) {
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
    CIndice winners;
    CIndice pairs(data.size());
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
    CIndice sortedWinners = sortIndices(winners, data);

    // insertion
    CIndice finalChain = sortedWinners;
    // immediatly insert first
    finalChain.insert(finalChain.begin(), pairs[sortedWinners[0]]);

    // jacobsthal loop
    size_t nPending = sortedWinners.size() - 1;
    CData jacob = genJacobsthal(indices.size());
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
        typename CData::iterator pos =
            std::upper_bound(finalChain.begin(), finalChain.end(), loserIdx,
                             CompareIndices(data));

        finalChain.insert(pos, loserIdx);
      }
      lastJacobIdx = currentJacobIdx;
    }

    // restore straggler
    if (hasStraggler) {
      typename CData::iterator pos =
          std::upper_bound(finalChain.begin(), finalChain.end(), stragglerIdx,
                           CompareIndices(data));
      finalChain.insert(pos, stragglerIdx);
    }

    return finalChain;
  }

  void sort() {
    CIndice indices;
    for (size_t i = 0; i < _data.size(); i++)
      indices.push_back(i);
    CIndice sortedIndices = sortIndices(indices, _data);
    CData reconstructedData;
    for (size_t i = 0; i < sortedIndices.size(); i++)
      reconstructedData.push_back(_data[sortedIndices[i]]);
    _data = reconstructedData;
  }

  /**
   * @note a(n) = a(n-1) + 2*a(n-2), with a(0) = 0, a(1) = 1; also a(n) =
   * nearest integer to 2^n/3
   * @todo optimize
   *
   * @see https://oeis.org/A001045
   * @see https://en.wikipedia.org/wiki/Jacobsthal_number
   */
  _C<ulong, _A> genJacobsthal(size_t len) {
    _C<ulong, _A> j;
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
