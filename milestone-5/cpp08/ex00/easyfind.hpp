#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <stdexcept>

/**
 * @throws out_of_range
 */
template <typename T> int easyfind(T v, const int &el) {
  for (unsigned int i = 0; i < v.size(); i++)
    if (v[i] == el)
      return v[i];
  throw std::out_of_range("could not find value.");
}

#endif // !EASYFIND_HPP
