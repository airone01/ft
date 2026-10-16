#include "symtab.h"
#include <search.h>
#include <stdlib.h>
#include <string.h>

void *sym_table = NULL;
int current_local_offset = -4;
int current_param_offset = 8;
int string_counter = 0;
int label_counter = 1;

void add_symbol(char *name, SymbolType type) {
  Symbol *sym = malloc(sizeof(Symbol));
  sym->name = strdup(name);
  sym->type = type;

  switch (type) {
  case TYPE_AUTO:
    sym->offset = current_local_offset;
    current_local_offset -= 4; // shift down 4 for next var
    break;
  case TYPE_PARAM:
    sym->offset = current_param_offset;
    current_param_offset += 4; // shift up 4 for next var
    break;
  case TYPE_EXTERN:
    sym->offset = 0;
    break;
  }

  // insertion
  Symbol **found = tsearch(sym, &sym_table, compare_symbols);
  if (*found != sym) {
    // var was already in the tree
    free(sym->name);
    free(sym);
  }
}

Symbol *get_symbol(char *name) {
  Symbol dummy;
  dummy.name = name;
  Symbol **found = tfind(&dummy, &sym_table, compare_symbols);
  if (found) {
    return *found;
  }
  return NULL;
}

// required by tsearch
int compare_symbols(const void *pa, const void *pb) {
  return strcmp(((const Symbol *)pa)->name, ((const Symbol *)pb)->name);
}
