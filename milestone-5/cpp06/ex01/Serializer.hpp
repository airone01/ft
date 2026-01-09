#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"
#include <stdint.h>

class Serializer {
public:
  static uintptr_t serialize(Data *ptr);
  static Data *deserialize(uintptr_t raw);

private:
  // 98 doesn't have `= delete` so this will do
  Serializer();
  Serializer(const Serializer &);
  ~Serializer();
  Serializer &operator=(const Serializer &);
};

#endif // !SERIALIZER_HPP
