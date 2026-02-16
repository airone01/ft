#include "PmergeMe.hpp"
#include <ctime>
#include <deque>
#include <exception>
#include <iomanip>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " <positive integer sequence[s...]>"
              << std::endl;
    return 1;
  }

  std::string in(argv[1]);
  if (argc > 2) {
    for (size_t i = 2; i < static_cast<size_t>(argc); i++)
      in.append(argv[i]);
  }

  try {
    typedef std::vector<unsigned long> vulong;
    typedef std::deque<unsigned long> qulong;
    PmergeMe<vulong> pv(in);
    PmergeMe<qulong> pq(in);

    std::cout << "Before: " << pv.getData() << std::endl;

    struct timespec vBegin, vEnd, qBegin, qEnd;

    clock_gettime(CLOCK_MONOTONIC, &vBegin);
    pv.sort();
    clock_gettime(CLOCK_MONOTONIC, &vEnd);

    clock_gettime(CLOCK_MONOTONIC, &qBegin);
    pq.sort();
    clock_gettime(CLOCK_MONOTONIC, &qEnd);

    double vNsTime = (static_cast<double>(vEnd.tv_sec - vBegin.tv_sec) * 1.0e9 +
                      static_cast<double>(vEnd.tv_nsec - vBegin.tv_nsec));
    double qNsTime = (static_cast<double>(qEnd.tv_sec - qBegin.tv_sec) * 1.0e9 +
                      static_cast<double>(qEnd.tv_nsec - qBegin.tv_nsec));

    std::cout << "After : " << pv.getData() << std::endl
              << std::setprecision(5);
    std::cout << "Vector time: " << vNsTime << "ns" << " (≈" << vNsTime / 1.0e9
              << "s)" << std::endl;
    std::cout << "Deque time : " << qNsTime << "ns" << " (≈" << qNsTime / 1.0e9
              << "s)" << std::setprecision(0) << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
