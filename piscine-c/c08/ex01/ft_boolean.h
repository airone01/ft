
#ifndef FT_BOOLEAN_H
#define FT_BOOLEAN_H

#include <unistd.h>

typedef enum e_bool {
  FALSE = 0,
  TRUE = 1,
} t_bool;

#define SUCCESS 0

#define ODD_MSG "I have an odd number of arguments."
#define EVEN_MSG "I have an even number of arguments."

#define EVEN(nbr) ((nbr % 2) == 0 ? TRUE : FALSE)

#endif
