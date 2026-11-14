#ifndef PRINT_H
#define PRINT_H

#include "args.h"
#include "symbol.h"
#include <stddef.h>

/**
 * Pretty-prints symbols
 */
void syms_print(const Symbol *syms, size_t nmemb, int is_64bit, Options opts);

/**
 * Sorts symbols
 *
 * @note It should sort pretty much the same as GNU BinUtils's nm.
 */
void syms_sort(Symbol *syms, size_t nmemb, Options opts);

#endif /* PRINT_H */
