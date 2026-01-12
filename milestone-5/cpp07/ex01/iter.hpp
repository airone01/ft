#ifndef ITER_HPP
#define ITER_HPP

template <typename T, typename F> void iter(T *v, const int l, F f) {
  for (int i = 0; i < l; i++) {
    f(v[i]);
  }
}

#endif // !ITER_HPP
