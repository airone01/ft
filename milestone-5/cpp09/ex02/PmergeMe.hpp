#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <deque>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

typedef unsigned long ulong;

/**
 * @tparam _C container type
 * @tparam _A STD allocator
 */
template <template <class, class> class _C, class _A> struct CompareIndices {
  const _C<ulong, _A> &_data;
  CompareIndices<_C, _A>(const _C<ulong, _A> &data) : _data(data) {}
  bool operator()(size_t a, size_t b) const { return _data[a] < _data[b]; }
};

/**
 * @tparam _C container type
 * @tparam _A STD allocator
 *
 * @note a(n) = a(n-1) + 2*a(n-2), with a(0) = 0, a(1) = 1; also a(n) = nearest
 * integer to 2^n/3
 * @TODO optimize
 *
 * @see https://oeis.org/A001045
 * @see https://en.wikipedia.org/wiki/Jacobsthal_number
 */
template <template <class, class> class _C, class _A>
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

class PmergeMe {
private:
  std::vector<ulong> _vec;
  std::deque<ulong> _deq;

public:
  // OCF
  PmergeMe();
  PmergeMe(const PmergeMe &);
  PmergeMe operator=(const PmergeMe &);
  ~PmergeMe();

  PmergeMe(const std::string &s);

  void sortVector();
  void sortDeque();

  /**
   * @tparam _C container type
   * @tparam _A STD allocator
   */
  template <template <class, class> class _C, class _A>
  _C<size_t, _A> sortIndices(_C<size_t, _A> &indices, _C<ulong, _A> &data) {
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
    _C<ulong, _A> winners;
    _C<ulong, _A> pairs(data.size());
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
    _C<size_t, _A> sortedWinners = sortIndices(winners, data);

    // insertion
    _C<size_t, _A> finalChain = sortedWinners;
    // immediatly insert first
    finalChain.insert(finalChain.begin(), pairs[sortedWinners[0]]);

    // jacobsthal loop
    size_t nPending = sortedWinners.size() - 1;
    _C<ulong, _A> jacob = genJacobsthal<_C, _A>(indices.size());
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
        typename _C<ulong, _A>::iterator pos =
            std::upper_bound(finalChain.begin(), finalChain.end(), loserIdx,
                             CompareIndices<_C, _A>(data));

        finalChain.insert(pos, loserIdx);
      }
      lastJacobIdx = currentJacobIdx;
    }

    // restore straggler
    if (hasStraggler) {
      typename _C<ulong, _A>::iterator pos =
          std::upper_bound(finalChain.begin(), finalChain.end(), stragglerIdx,
                           CompareIndices<_C, _A>(data));
      finalChain.insert(pos, stragglerIdx);
    }

    return finalChain;
  }

  /**
   * @tparam _C container type
   * @tparam _A STD allocator
   */
  template <template <class, class> class _C, class _A>
  void sort(_C<ulong, _A> &c) {
    _C<size_t, _A> indices;
    for (size_t i = 0; i < c.size(); i++)
      indices.push_back(i);

    _C<size_t, _A> sortedIndices = sortIndices(indices, c);

    _C<ulong, _A> reconstructedData;
    for (size_t i = 0; i < sortedIndices.size(); i++)
      reconstructedData.push_back(c[sortedIndices[i]]);

    c = reconstructedData;
  }

  const std::vector<ulong> &getVector() const;
  const std::deque<ulong> &getDeque() const;

  class InvalidInputException : public std::exception {
    virtual const char *what() const throw();
  };
};

/**
 * @brief formats a container for an ostream
 * @note this exists because `fmt` and other solutions don't exist in 98
 * @note the template shenanigans are to indicate to the compiler to accept only
 * containers for arg `c`
 * @note tested with `std::vector` and `std::deque`
 */
template <template <typename, typename> class Container, typename Alloc>
std::ostream &operator<<(std::ostream &os,
                         const Container<unsigned long, Alloc> &c) {
  typename Container<unsigned long, Alloc>::const_iterator it = c.begin();
  os << "[";
  while (it != c.end()) {
    os << *it;
    if (++it != c.end()) {
      os << ",";
      // os << std::endl;
    }
  }
  os << "]";
  return os;
}

#endif // !PMERGEME_HPP
