#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

/*
 * Easyfind must support multiple container types.
 * I purposely used `std::find` to allow support for containers that won't
 * handle `operator[]`.
 *
 * I am guessing there will be a test for this during the defense :-)
 */

/**
 * @throws out_of_range
 * @param c container
 */
template <class T> int easyfind(T c, const int &el) {
  typename T::iterator it = std::find(c.begin(), c.end(), el);
  if (it == c.end())
    throw std::out_of_range("could not find value.");
  return *it;
}

#endif // !EASYFIND_HPP
