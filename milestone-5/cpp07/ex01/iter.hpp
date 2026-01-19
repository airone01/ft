#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <class T, class F> void iter(T *v, const size_t l, F f) {
  for (size_t i = 0; i < l; i++) {
    f(v[i]);
  }
}

#endif // !ITER_HPP
