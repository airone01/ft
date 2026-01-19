#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

/**
 * @brief Swaps the values of two given parameters.
 */
template <class T> void swap(T &a, T &b) {
  T tmp = a;
  a = b;
  b = tmp;
}

/**
 * @brief Compares the two values passed as parameters and returns the smallest
 * one.
 * @note If they are equal, it returns the second one.
 */
template <class T> T min(T a, T b) {
  return (a < b) ? a : b;
}

/**
 * @brief Compares the two values passed as parameters and returns the greatest
 * one.
 * @note If they are equal, it returns the second one.
 */
template <class T> T max(T a, T b) {
  return (a > b) ? a : b;
}

#endif // !TEMPLATE_HPP
